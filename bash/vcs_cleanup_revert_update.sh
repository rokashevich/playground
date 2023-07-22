#!/bin/bash
if [ -z $1 ]
then
    echo "Usage: $0 /path/to/repos"
    exit 1
fi

read -p 'Username: ' USERNAME
read -sp 'Password: ' PASSWORD
echo $USERNAME":"$PASSWORD
echo

REPOS=$1
find $REPOS/* -maxdepth 0 -type d|while IFS= read -r REPO
do 
pushd $REPO >/dev/null
pwd
if [ -d '.svn' ]
then
echo "in "$REPO
svn --username=$USERNAME --password=$PASSWORD cleanup --remove-unversioned --remove-ignored
svn --username=$USERNAME --password=$PASSWORD revert -R .
svn --username=$USERNAME --password=$PASSWORD up
elif [ -d '.git' ]
then
echo "GIT "$REPO
#git clean -fdx
#git reset --hard HEAD
#git pull
else
echo "UNKNOWN "$REPO
fi
popd >/dev/null
done