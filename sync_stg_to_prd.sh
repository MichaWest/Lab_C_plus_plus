git checkout prd

git merge stg -m "Перенос из stg в prd"

$tag = "prd-" + (Get-Date -Format "yyyyMMdd-HHmmss")
git tag $tag -m "Тег от $(Get-Date)"

git push origin prd
git push origin $tag

git checkout stg