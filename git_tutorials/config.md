# GIT Configuration

See `~/.gitconfig` for the global configuration

## list all config fields
`git config --list`

## get specifit config field 
`git config --get <key>.<val>`

## set name 
`git config --add --global user.name <full_name>`

## set email
`git config --add --global user.email <email>`

## remove a key 
`git config --unset <key>.<val>`

`git config --unset-all <key>.<val>`

## Default branch

To set the default branch do

`git config --add --global init.defaultBranch master`

Note:
- on Git default is `master` 
- on Github default is `main` 
