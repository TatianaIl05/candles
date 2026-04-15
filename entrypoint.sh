#!/bin/bash

# Если это GitLab CI — просто выводим HTML в stdout
if [ -n "$CI" ]; then
    kubectl logs -l app=test-repo-app --tail=-1 2>&1 | sed 's/$/<br>/'
    exit 0
fi

# Иначе — обычный режим для Kubernetes (с nginx)
> /usr/share/nginx/html/index.html

if command -v kubectl &> /dev/null && kubectl get pods -l app=test-repo-app &> /dev/null; then
    POD_NAME=$(kubectl get pods -l app=test-repo-app --field-selector status.phase=Running -o name | head -n 1)
    if [ -n "$POD_NAME" ]; then
        kubectl logs "$POD_NAME" --tail=-1 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
        nginx -g "daemon off;"
        exit
    fi
fi

nginx -g "daemon off;"