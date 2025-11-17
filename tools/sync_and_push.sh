#!/usr/bin/env bash

# Define paths
my_repo=~/ab
project=$(pwd)
project_name=$(basename "$project")
target="$my_repo/$project_name"
commit_msg="$1"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Syncing project with repository...${NC}"

# Check for commit message argument
if [ -z "$commit_msg" ]; then
  echo -e "${RED}Usage: syncpush \"Your commit message here\"${NC}"
  exit 1
fi

# Check if current directory is a Git repository
if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
  echo -e "${RED}Error: Current directory is not a Git repository.${NC}"
  exit 1
fi

# Check for unstaged changes
if ! git status --porcelain | grep -q '^[ M][^?]'; then
  echo -e "${GREEN}No changes to commit. Project is clean.${NC}"
  exit 0
fi

echo -e "${YELLOW}Unstaged changes detected. Proceeding with sync...${NC}"

# Ensure target folder exists
mkdir -p "$target"

# Sync project contents into its dedicated folder
echo -e "${YELLOW}Mirroring '$project' to '$target'...${NC}"
rsync -a --delete --exclude='.git/' "$project/" "$target/"

# Commit and push changes in the project
echo -e "${YELLOW}Committing and pushing changes in the project...${NC}"
git add .
git commit -m "$commit_msg"
git push

# Commit and push changes in the mirrored repo
echo -e "${YELLOW}Committing and pushing changes in the repository...${NC}"
cd "$target" || exit
git add .
git commit -m "$commit_msg"
git push

echo -e "${GREEN}Sync complete.${NC}"
