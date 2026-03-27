#!/bin/bash

CURRENT_BRANCH=$(git branch --show-current)

git checkout -b stg 2>/dev/null || git checkout stg

git merge dev -m "Перенос из dev в stg"

tag="stg-$(date +'%Y%m%d-%H%M%S')"
git tag "$tag" -m "Тег от $(date)"

git push origin stg
git push origin "$tag"

git checkout CURRENT_BRANCH
