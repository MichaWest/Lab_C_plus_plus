#!/bin/bash

CURRENT_BRANCH=$(git branch --show-current)

git checkout -b prd 2>/dev/null || git checkout prd

git merge stg -m "Перенос из stg в prd"

tag="prd-$(date +'%Y%m%d-%H%M%S')"
git tag $tag -m "Тег от $(Get-Date)"

git push origin prd
git push origin "$tag"

git checkout CURRENT_BRANCH