# Git Commits

Resource: [Learn Git Branching](https://learngitbranching.js.org/)

### Show commits

```bash
git log             # show all commits, hashes, and messages
git log -n5         # last 5 commits
git log --oneline   # show short form of commits and messages
git log --pretty=%H # show full hash on one line
```

### Commit a new change

`git commit -m <msg>`

---

### Branching

`git branch <bname> <ref_commit>|<ref_branch>` 

Examples
```bash
git branch bugFix HEAD^2~2    # 1. branch of a relative reference
git branch branch1 commit1    # 2. branch of commit1
git branch branch2 branch1    # 3. branch of branch1
```

**Note**: ex1..3 will not move the head off of main

**or** you can branch of the currently active branch:

- make `git branch <bname>`
- move into `git checkout <bname>`
- make and move into `git checkout -b <bname>`

As you commit on the new branch the head moves with the commits

---

### Merging branch to curently active branch

`git merge <branch>` *into the curently active branch*

This will create a new commit on the active branch and link `branch` to the active branch. This means that you have to `checkout` the branch that you want the commit to be merged into.

- merge `b1` into `main`: 
  - `git checkout main`
  - `git merge b1`

---

### Rebasing

`git rebase <dest_branch>` *with currently active branch* 
`git rebase <source_branch> <dest_branch>`

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

---

### HEAD

HEAD is the symbolic name for the currently checked out commit -- it's essentially what commit you're working on top of

HEAD always points to the most recent commit which is reflected in the working tree.

Normally HEAD points to a branch name (like bugFix).

#### Detaching HEAD

Detaching HEAD just means attaching it to a commit instead of a branch.

Normally HEAD points to main which in turn points to the last commit. 

By doing `git checkout <commit_hash>` will make the head point directly to the commit. 

#### Relative references

You can **move the HEAD** relative to it's current position in two ways:

1. `^<n>` or `[^...]`  go to parent; i.e `^^`. if `^2` then the second parent is chosen (like in the case of `merge`)
   
2. `~<n>` move up *n* times, ex `~3` moves the head 3 commmits from curent position

**Usage**

`git checkout HEAD~3`

`git checkout HEAD^`

---

### Branch forcing

You can directly reassign a branch to a commit with the `branch -f`.

This can be used togheter with relative ref see above..

**Usage**

`git branch -f <branch> <dest_commit>`

ex `git branch -f main HEAD~3` moves main 3 commits before head

It is important to note that git branch -f cannot be used to force update a branch that is currently checked out in the working directory.

---

### Undo (reversing) changes

There are 2 ways of undoing changes:
- `git reset` local branch
- `git revert` local and remote branches

#### git reset

Moves branch reference back to an older commit
ex: `git reset HEAD~1`

#### git revert

Revert will push a new commmit with the changes of the reversal.
ex: `git revert HEAD` will create a nea commit with the last changes undone. 

The idea is to `reset` the local branch and then `revert` the remote
branch to match 

---

### Cherry-pick

`git cherry-pick <Commit1> <Commit2> <...>`

Copy a series of commits below your current location (HEAD). The commits do not have to be in order.

You can also cherry-pick a branch, but that will copy only the head 
of that branch

The commits can be on other branches. 

---

### Interactive rebase

`git rebase -i <dest>`

This brings up a file with all the commits that you can perform different operenations on:
  - drop/omit
  - rearenge
  - ...

---

### Typical cases

#### Copy only one change

Say you have multiple commits in a row and you want to **copy only one of the commits over**.

Solution: `git cherry-pick` or `git rebase -i`

ex:

You have following branches: *main > debug > printf > bugFix* and you copy only the **bugFix to main**

```bash
$ git checkout main # checkout main
$ git cherry-pick bugFix # copy bugFix to main (only head is copied)
```

#### Make small modification to previous commit

You can implement a small change to a previous commit using this strategy:
1. use `rebase -i main` and bring up the commit to change
2. use `commit --amend` to make the *small* modification
3. use `rebase -i main` to bring the tree back to original form
4. user `git branch -f main <last_commit>` to bring main to top

---

### TAGS

`git tag <tag_name> <commit>`

`git tag <tag_name>` this will apply the tag to the head.

Permanently mark historical points in your project's history. For things like major releases and big merges. 

**Note**: you can't commit directly to a tag. So doing `commit` will put you in a *detached head* mode

You can use `git describe <commit> | <branch>` to see how far that commit or branch is from the closes tag

the output is `<tag>-<n>-g<commit>` where:
- `tag` closest tag
- `n` number of commits to that tag
- `commit` to the commit in the `describe` command
