call plug#begin('~/.vim/plugged')
Plug 'mhinz/vim-startify'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
call plug#end()

" 语法高亮
syntax enable
syntax on

" vim 配置
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
"set nu                 "  
set autoindent
set cindent

" airline 配置
set t_Co=256                                    "不显示彩色的结症所在啊！！！ 
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 1    "显示窗口tab和buffer  
if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif
" old vim-powerline symbols
let g:airline_left_sep = '⮀'
let g:airline_left_alt_sep = '⮁'
let g:airline_right_sep = '⮂'
let g:airline_right_alt_sep = '⮃'
let g:airline_symbols.branch = '⭠'
let g:airline_symbols.readonly = '⭤'
let g:airline_symbols.linenr = '¶'
let laststatus=1                                                "永远显示状态栏
let g:airline_theme='supernova'                                     "选择主题
let g:airline#extensions#tabline#left_sep = ' '                 "separater
let g:airline#extensions#tabline#left_alt_sep = '|'             "separater
let g:airline#extensions#tabline#formatter = 'default'          "formater