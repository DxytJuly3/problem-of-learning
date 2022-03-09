call plug#begin('~/.vim/plugged')
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'jiangmiao/auto-pairs'
call plug#end()

" 语法高亮
syntax enable
syntax on
" AutoPairs 插件 配置
let g:AutoPairsShortcutJump = '<M-n>'   "设置调到下一层括号对的快捷键，默认为ALT+n。 
let g:AutoPairs = {'(':')', '[':']', '{':'}',"'":"'",'"':'"'}
let g:AutoPairsMapBS = 1    "把BACKSPACE键映射为删除括号对和引号，默认为1。 
let g:AutoPairsMapCR = 1    "把ENTER键映射为换行并缩进，默认为1。
let g:AutoPairsMapSpace = 1 "把SPACE键映射为在括号两侧添加空格，默认为1。

"vim 配置
set backspace=2
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set nu                 "  
set autoindent
set cindent

" airline 配置
set t_Co=256            "不显示彩色的结症所在啊！！！ 
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
let laststatus=1               "永远显示状态栏
let g:airline_theme='supernova'        "选择主题
let g:airline#extensions#tabline#left_sep = ' '     "separater
let g:airline#extensions#tabline#left_alt_sep = '|' "separater
let g:airline#extensions#tabline#formatter = 'default'  "formater