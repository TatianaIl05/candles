# C++ Test Application with GitLab CI/CD and Kubernetes

A complete CI/CD pipeline for a C++ application with automated testing, Docker containerization, Kubernetes deployment via Helm, and test results published on GitLab Pages.

## Table of Contents

- [Project Overview](#project-overview)
- [Prerequisites](#prerequisites)
- [Running Locally](#running-locally)
- [CI/CD Pipeline](#cicd-pipeline)
- [GitLab Setup](#gitlab-setup)
- [Kubernetes Deployment](#kubernetes-deployment)
- [GitLab Pages](#gitlab-pages)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Troubleshooting](#troubleshooting)

## Project Overview

This project demonstrates:
- C++ application with Google Test framework
- Docker containerization (multi-stage builds)
- GitLab CI/CD pipeline with 5 stages
- Automated testing and test result publishing
- Helm chart for Kubernetes deployment
- Rolling updates in Kubernetes
- GitLab Pages for test results visualization

## Prerequisites

### Local Development
- Docker and Docker Compose
- Kubernetes cluster (Minikube for local testing)
- Helm 3.x
- Git

### GitLab CI/CD
- GitLab account
- GitLab Runner with Docker executor
- Docker Hub account (for images)

## Running Locally

### Option 1: Using Docker Compose

Clone repository:
```
git clone https://gitlab.com/tatianail051/test-repo.git
cd test-repo
```
Build and run:
```
docker-compose up --build
```
Run tests only:
```
docker run --rm test-repo-app ./build/testproj
```
### Option 2: Using Docker

Build images:
```
docker build -t test-repo-app -f Dockerfile.app .
docker build -t test-repo-web -f Dockerfile.web .
```
Run C++ tests:
```
docker run --rm test-repo-app ./build/testproj
```
Run web server:
```
docker run -p 8080:80 test-repo-web
```
### Option 3: Using Kubernetes and Helm

Start Minikube:
```
minikube start
```
Deploy application:
```
helm install test-release ./helm/test-repo-chart
```
Check deployment:
```
kubectl get pods
kubectl get services
```
Access the application:
```
minikube service test-release-web
```
Update deployment (simulates rolling update):
```
helm upgrade test-release ./helm/test-repo-chart --set app.image=your-image:new-tag
```
Uninstall:
```
helm uninstall test-release
```
## GitLab Setup

### 1. Configure CI/CD Variables

Go to Settings -> CI/CD -> Variables and add:

DOCKERHUB_USERNAME - Docker Hub username (example: yourusername)
DOCKERHUB_PASSWORD - Docker Hub password/token (example: dckr_pat_xxxxx)
KUBE_CONFIG - Kubernetes kubeconfig base64 encoded
HELM_RELEASE_NAME - Helm release name (example: test-release)

### 2. Set Up GitLab Runner

Register a Docker executor runner:
```
docker run --rm -it -v /srv/gitlab-runner/config:/etc/gitlab-runner \
  gitlab/gitlab-runner:latest register
```
When prompted:
- URL: https://gitlab.com/
- Token: from Settings -> CI/CD -> Runners
- Executor: docker
- Default image: docker:20.10

### 3. Trigger Pipeline

Create and push a tag to trigger the pipeline:
```
git tag v1.0.0
git push origin v1.0.0
```
## CI/CD Pipeline

The pipeline consists of 5 stages:

### Stage 1: Build
- Builds Docker images for C++ app and web server
- Saves images as artifacts for subsequent stages

### Stage 2: Test
- Loads the built image
- Runs C++ tests using Google Test
- Captures test output as artifact

### Stage 3: Publish
- Pushes Docker images to Docker Hub
- Only runs if tests pass

### Stage 4: Deploy
- Deploys to Kubernetes using Helm
- Supports rolling updates
- Manual trigger option for production

### Stage 5: Pages
- Generates HTML from test results
- Publishes to GitLab Pages

## Kubernetes Deployment

### Helm Chart Structure

helm/test-repo-chart/
- Chart.yaml          # Chart metadata
- values.yaml         # Default configuration values
- templates/
  - deployment.yaml   # App deployment
  - service.yaml      # Service definitions

### Configuration Options

In values.yaml:
app:
  image: test-repo-app
  tag: latest
  replicaCount: 2

web:
  image: test-repo-web
  tag: latest
  replicaCount: 1

### Rolling Update Demo

Update application:
```
git add .
git commit -m "New feature"
git tag v1.1.0
git push origin v1.1.0
```
Watch rolling update:
```
kubectl rollout status deployment/test-release-app
kubectl get pods -w
```
## GitLab Pages

### Access Test Results

After pipeline completes, visit:
https://<your-gitlab-username>.gitlab.io/<project-name>/

### What's Published
- C++ test execution output

### Helm Repository Publishing

Helm charts are also published to Pages at:
https://<username>.gitlab.io/<project>/helm/

Add this repository to Helm:
```
helm repo add my-repo https://<username>.gitlab.io/<project>/helm
helm repo update
```
## Project Structure

test-repo/
- .gitlab-ci.yml          # CI/CD pipeline configuration
- Dockerfile.app          # C++ application container
- Dockerfile.web          # Web server container
- entrypoint.sh           # Web server entrypoint
- CMakeLists.txt          # CMake configuration
- main.cpp                # Main C++ application
- candle.cpp              # Application logic
- candle.h
- testproj                # Test binary
- helm/
  - test-repo-chart/      # Helm chart
    - Chart.yaml
    - values.yaml
    - templates/
- README.md               # This file

## Dependencies

### C++ Application
- CMake 3.10+
- Google Test (libgtest-dev)
- GCC compiler

### Docker Images
- gcc:latest - Build stage
- nginx:latest - Web server
- alpine:latest - CI jobs

### Kubernetes Tools
- kubectl 1.23+
- Helm 3.10+
- Minikube (local development)

### GitLab CI
- GitLab Runner with Docker executor
- Docker-in-Docker service

## Troubleshooting

### Docker daemon connection error

Ensure your GitLab Runner has Docker socket mounted:
```
docker run -v /var/run/docker.sock:/var/run/docker.sock
```
### Kubernetes connection timeout

For Minikube, use host.docker.internal:
```
sed -i 's|127.0.0.1|host.docker.internal|g' ~/.kube/config
```
### Pages not showing

- Check that public/ directory contains index.html
- Verify artifacts are being saved
- Check Pipeline -> Pages job logs

### Test failures

View test output in GitLab:
- Go to CI/CD -> Pipelines
- Click on test_app job
- Check the job logs for detailed test output
