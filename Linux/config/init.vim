call plug#begin('~/.config/nvim/plugged')
Plug 'dense-analysis/ale'
Plug 'rhysd/vim-clang-format'
Plug 'neoclide/coc.nvim', {'branch': 'master'}
Plug 'mg979/vim-xtabline'
Plug 'liuchengxu/vista.vim'
Plug 'bling/vim-airline'
Plug 'majutsushi/tagbar'
"Plug 'itchyny/lightline.vim'
Plug 'dracula/vim', { 'as': 'dracula' }
Plug 'ajmwagar/vim-deus'
Plug 'vim-airline/vim-airline-themes'
Plug 'jiangmiao/auto-pairs'
Plug 'octol/vim-cpp-enhanced-highlight' " C++ 高亮
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
call plug#end()

set noshowmode
set relativenumber " 相对行号
set helplang=cn
set ambiwidth=double                                        
" 设置UTF-8编码
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
" 设置行数显示
set number
set softtabstop=4
set tabstop=4   "tab长度
set shiftwidth=4   " 缩进长度
set termguicolors

nmap <C-z> <Cmd>:bn<CR>

" = = = = = = = = = airline = = = = = = = = =
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 0
let g:airline#extensions#tabline#buffer_nr_show = 1
" 关闭状态显示空白符号计数
let g:airline#extensions#whitespace#enabled = 0
let g:airline#extensions#whitespace#symbol = '!'
" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
                                                            
" powerline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''

" old vim-powerline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''

" = = = = = = = = = = airline_theme = = = = = = = = = =
" let g:airline_theme="deus"
let g:airline_theme="dracula"


"= = = = = = = = = = coc.nvim = = = = = = = = = = = 
" Tab 补全
inoremap <silent><expr> <TAB>
\ coc#pum#visible() ? coc#_select_confirm() :
\ coc#expandableOrJumpable() ?
\ "<C-r>=coc#rpc#request('doKeymap', ['snippets-expand-jump',''])<CR>" :
\ CheckBackspace() ? "<TAB>" :
\ coc#refresh()

function! CheckBackspace() abort
let col = col('.') - 1
return !col || getline('.')[col - 1] =~# '\s'
endfunction

let g:coc_snippet_next = '<tab>'
" coc加载
set updatetime=100

"= = = = = = = = = = = xtabline = = = = = = = = = = = =
let g:xtabline_settings = {}
let g:xtabline_settings.enable_mappings = 0
let g:xtabline_settings.tabline_modes = ['tabs', 'buffers']
let g:xtabline_settings.enable_persistance = 0
let g:xtabline_settings.last_open_first = 1
let g:xtabline_settings.theme = "dracula"
noremap \p :echo expand('%:p')<CR>
" 自定义tabline
set showtabline=2

"= = = = = = = = = = = vim-theme = = = = = = = = = = = =
set background=dark    " Setting dark mode
colorscheme dracula 
let g:deus_termcolors=256


" explorer 快捷
nmap ff <Cmd>CocCommand explorer<CR>
" Close Coc-explorer if it is the only window
autocmd BufEnter * if (&ft == 'coc-explorer' && winnr("$") == 1) | q | endif


"= = = = = = = = = = = Vista = = = = = = = = = = = =
let g:vista_default_executive = 'ctags'
let g:vista_executive_for = {}
let g:vista_ctags_cmd = {
      \ 'haskell': 'hasktags -x -o - -c',
      \ }
let g:vista_fzf_preview = ['right:50%']
let g:vista#renderer#enable_icon = 1
let g:vista#renderer#icons = {
\   "function": "\uf794",
\   "variable": "\uf71b",
\  }

"= = = = = = = = = = = tagbar = = = = = = = = = = = =
let g:tagbar_width=30
" 将tagbar的开关按键设置为 F4
nnoremap <silent> <F4> :TagbarToggle<CR>
" 启动 时自动focus
let g:tagbar_autofocus = 1

"= = = = = = = = = = = fzf = = = = = = = = = = = =
nmap <C-p> :Files<CR>
let g:fzf_layout = { 'down': '46%' }

"= = = = = = = = = clang-format = = = = = = = = =
autocmd FileType c,cpp,objc setlocal formatoptions-=cro
let g:clang_format_fallback_style = 'LLVM'
let g:clang_format_style_options = {
    \ 'BreakBeforeBraces': 'Custom',
    \ 'BraceWrapping': {
        \ 'AfterClass': v:false,
        \ 'AfterControlStatement': v:false,
        \ 'AfterEnum': v:false,
        \ 'AfterFunction': v:false,
        \ 'AfterNamespace': v:false,
        \ 'AfterObjCDeclaration': v:false,
        \ 'AfterStruct': v:false,
        \ 'AfterUnion': v:false,
        \ 'BeforeCatch': v:true,
        \ 'BeforeElse': v:true,
        \ 'IndentBraces': v:false,
    \ },
    \ 'PointerAlignment': 'Left',
    \ 'MaxEmptyLinesToKeep': 1,
    \ 'ReflowComments': v:false,
    \ 'SortIncludes': v:false,
    \ 'UseTab': 'Never',
    \ 'IndentWidth': 4,
    \ 'TabWidth': 4,
    \ 'AllowShortIfStatementsOnASingleLine': v:false,
    \ 'IndentCaseLabels': v:false,
    \ 'AccessModifierOffset': -4,
    \ }
autocmd FileType c,cpp,cc,hpp,h nnoremap <silent> <C-k> :ClangFormat<CR>
autocmd FileType c,cpp,cc,hpp,h nnoremap <silent> <M-/> :execute "normal! I//\e"<CR>
