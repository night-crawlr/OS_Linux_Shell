import os
import sys
import io
os.system("git init")
os.system("git add *")
os.system("git commit -m \"Upload Files\"")
os.system("git rm --cached github_upload.py")
os.system("git commit -m \"Deleted github_upload.py\"")
os.system("git branch -M main")
URL = input()
os.system("git remote add origin " + URL)
os.system("git push -u origin main")
print("DONE!")
