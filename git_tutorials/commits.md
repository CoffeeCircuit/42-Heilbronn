# Git Commits

Resource: [Learn Git Branching](https://learngitbranching.js.org/)

## Commands

### Commit a new change

`git commit -m <msg>`

### Make a new branch and move onto the new branch

- make `git branch <bname>`
- move `git checkout <bname>`
- make and move `git checkout -b <bname>`

As you commit on the new branch the head moves with the commits

### Merging branch to curently active branch

`git merge <branch>` *into the curently active branch*

This will create a new commit on the active branch and link `branch` to the active branch. This means that you have to `checkout` the branch that you want the commit to be merged into.

- merge `b1` into `main`: 
  - `git checkout main`
  - `git merge b1`

### Rebasing

`git rebase <dest_branch>` *with currently active branch* 

- copy current active branch `b1` to `main`: 
  - `git checkout b1`
  - `git rebase main`
- move main (as parent) to `b1` 
  - `git checkout main`
  - `git rebase b1`
- move main (from another branch) to `b1`
  - `git branch -f main b1`

This makes of copy of the branch on 
The advantage of rebasing is that it can be used to make a nice linear sequence of commits. The commit log / history of the repository will be a lot cleaner if only rebasing is allowed.

