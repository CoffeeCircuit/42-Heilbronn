return {
	{
		"mason-org/mason.nvim",
		config = function()
			require("mason").setup()
		end,
	},
	{
		"williamboman/mason-nvim-dap.nvim",
		dependencies = { "mfussenegger/nvim-dap" },
		config = function()
			require("mason-nvim-dap").setup({
				ensure_installed = { "codelldb" }, -- auto install codelldb
				automatic_installation = true,
			})
		end,
	},
}
