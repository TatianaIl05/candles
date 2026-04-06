#!/bin/bash
docker logs test-repo-app 2>&1 | sed 's/$/<br>/' > /usr/share/nginx/html/index.html
nginx -g "daemon off;"