return {
	{
		"mfussenegger/nvim-dap",
		dependencies = {
			"rcarriga/nvim-dap-ui",
			"nvim-neotest/nvim-nio"
		},
		keys = {
			-- Basic debugging keymaps, feel free to change to your liking!
			{
				'<F5>',
				function()
					require('dap').continue()
				end,
				desc = 'Debug: Start/Continue',
			},
			{
				'<F11>',
				function()
					require('dap').step_into()
				end,
				desc = 'Debug: Step Into',
			},
			{
				'<F10>',
				function()
					require('dap').step_over()
				end,
				desc = 'Debug: Step Over',
			},
			{
				'<F6>',
				function()
					require('dap').step_out()
				end,
				desc = 'Debug: Step Out',
			},
			{
				'<leader>b',
				function()
					require('dap').toggle_breakpoint()
				end,
				desc = 'Debug: Toggle Breakpoint',
			},
			{
				'<leader>B',
				function()
					require('dap').set_breakpoint(vim.fn.input 'Breakpoint condition: ')
				end,
				desc = 'Debug: Set Breakpoint',
			},
			-- Toggle to see last session result. Without this, you can't see session output in case of unhandled exception.
			{
				'<F7>',
				function()
					require('dapui').toggle()
				end,
				desc = 'Debug: See last session result.',
			},
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

				dap.listeners.after.event_initialized['dapui_config'] = dapui.open
				dap.listeners.before.event_terminated['dapui_config'] = dapui.close
				dap.listeners.before.event_exited['dapui_config'] = dapui.close

			end
		},
	}
