#!/bin/bash

> /usr/share/nginx/html/index.html

if command -v kubectl &> /dev/null && kubectl get pods -l app=repo-app &> /dev/null; then
    POD_NAME=$(kubectl get pods -l app=repo-app --field-selector status.phase=Running -o name | head -n 1)
    
    if [ -n "$POD_NAME" ]; then
        kubectl logs "$POD_NAME" --tail=-1 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
        # Если нашли и записали логи K8s, выходим из скрипта и запускаем nginx
        nginx -g "daemon off;"
        exit
    fi
elif docker ps &> /dev/null && docker logs repo-app &> /dev/null; then
    docker logs repo-app 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
fi

nginx -g "daemon off;"