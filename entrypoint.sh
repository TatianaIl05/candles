#!/bin/bash

# Если переменная GITLAB_PAGES=true, выводим HTML в stdout
if [ "$GITLAB_PAGES" = "true" ]; then
    kubectl logs -l app=test-repo-app --tail=-1 2>&1 | sed 's/$/<br>/'
    exit 0
fi

# Обычный режим для Kubernetes
> /usr/share/nginx/html/index.html

if command -v kubectl &> /dev/null && kubectl get pods -l app=test-repo-app &> /dev/null; then
    POD_NAME=$(kubectl get pods -l app=test-repo-app --field-selector status.phase=Running -o name | head -n 1)
    if [ -n "$POD_NAME" ]; then
        kubectl logs "$POD_NAME" --tail=-1 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
        nginx -g "daemon off;"
        exit
    fi
elif docker ps &> /dev/null && docker logs test-repo-app &> /dev/null; then
    docker logs test-repo-app 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
fi

nginx -g "daemon off;"