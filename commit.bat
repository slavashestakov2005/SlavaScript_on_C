set /p x="Commit text: "
git add .
git commit -m "%x%"
git push -u origin main
