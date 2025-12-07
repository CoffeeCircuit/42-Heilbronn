local g = vim.g
local map = vim.keymap.set

g.mapleader = " "
g.maplocalleader = " "

map('n', ';', ':')
map('n', '<leader>v', ':e $MYVIMRC<CR>')
map('n', '<leader>t', ':10sp|:term<CR>')
map('n', '<leader>f', ':Format42<CR><CR>')

-- terminal mode
map('t', '<Esc>', '<C-\\><C-N>')

map('v', "'", "di''<Esc>P")
map('v', '"' , 'di""<Esc>P')

-- Window navigation
map('n', '<C-h>', '<C-w><C-h>', { desc = 'Move focus to the left window' })
map('n', '<C-l>', '<C-w><C-l>', { desc = 'Move focus to the right window' })
map('n', '<C-j>', '<C-w><C-j>', { desc = 'Move focus to the lower window' })
map('n', '<C-k>', '<C-w><C-k>', { desc = 'Move focus to the upper window' })
