local g = vim.g
local cmd = vim.cmd
local opt = vim.opt
local map = vim.keymap.set

g.mapleader = " " 
g.maplocalleader = " "

opt.termguicolors=true
opt.syntax="enable"
opt.number=true
opt.relativenumber=true
opt.tabstop=4
--	opt.expandtab=true
opt.shiftwidth=4
opt.cursorline=true
opt.colorcolumn="80"
opt.ignorecase=true
opt.smartcase=true
opt.splitright=true
opt.splitbelow=true
opt.clipboard="unnamedplus"
opt.wildmenu=true
--	opt.hlsearch=false

map('n', ';', ':')
map('n', '<leader>v', ':e $MYVIMRC<CR>')

-- terminal mode
map('t', '<Esc>', '<C-\\><C-N>')
map('t', '<Del>', ':bd!<CR>')






-- bootstrap lazy
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
	vim.fn.system({
		"git",
		"clone",
		"--filter=blob:none",
		"https://github.com/folke/lazy.nvim.git",
		"--branch=stable", -- latest stable release
		lazypath,
	})
end
vim.opt.rtp:prepend(lazypath)
require('lazy').setup({
	{"folke/tokyonight.nvim"},
	{"catppuccin/nvim"},
	{
		"nvim-treesitter/nvim-treesitter", 
		branch = 'master', 
		lazy = false, 
		build = ":TSUpdate",
		config = function() 
			require'nvim-treesitter.configs'.setup({
				ensure_installed = { "c", "cpp", "python", "lua", "vim", 
				"vimdoc", "query", "markdown", "markdown_inline" },
				auto_install = true,
				highlight = {
					enable = true,
				},
			}) 
		end,
	},
	{
		"mason-org/mason.nvim",
		opts = {}
	},

	{
		"mfussenegger/nvim-dap",
		dependencies = {
			"rcarriga/nvim-dap-ui",
			"nvim-neotest/nvim-nio"
		},
		config = function()
			local dapui = require("dapui")
			local dap = require("dap")

			dapui.setup()

			dap.adapters.codelldb = {
				type = "server",
				port = "${port}",
				executable = {
					command = vim.fn.expand(
						"~/.local/share/nvim/mason/packages/codelldb/extension/adapter/codelldb"
					),
					args = { "--port", "${port}" },
				},
			}

			dap.configurations.cpp = {
				{
					name = "Launch file",
					type = "codelldb",
					request = "launch",
					program = function()
						    local file = vim.fn.expand('%:r')  -- current file without extension
							local bin = vim.fn.getcwd() .. "/" .. vim.fn.fnamemodify(file, ':t')
							return vim.fn.input('Path to executable: ', bin, 'file')
					end,
					cwd = '${workspaceFolder}',
					stopOnEntry = false,
				},
			}

			dap.configurations.c = dap.configurations.cpp
			dap.configurations.rust = dap.configurations.cpp


			dap.listeners.before.attach.dapui_config = function()
				dapui.open()
			end
			dap.listeners.before.launch.dapui_config = function()
				dapui.open()
			end
			dap.listeners.before.event_terminated.dapui_config = function()
				dapui.close()
			end
			dap.listeners.before.event_exited.dapui_config = function()
				dapui.close()
			end





			map('n', '<leader>db', dap.toggle_breakpoint, {})
			map('n', '<leader>dc', dap.continue, {})

		end
	},
})


cmd.colorscheme("catppuccin-mocha")
