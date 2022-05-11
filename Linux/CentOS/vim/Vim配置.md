"  使用vim-plug添加插件  
call plug#begin('~/.vim/plugged') 
Plug 'bling/vim-airline' 
Plug 'neoclide/coc.nvim' 
Plug 'vim-airline/vim-airline-themes' 
Plug 'octol/vim-cpp-enhanced-highlight' " C++ 高亮 
Plug 'preservim/nerdtree'               " 文件夹 
Plug 'kien/rainbow_parentheses.vim'     " 括号 
Plug 'majutsushi/tagbar'                " 函数显示 
Plug 'pangloss/vim-javascript' 
Plug 'Xuyuanp/nerdtree-git-plugin'      " NerdTree 显示 git 状态 
Plug 'iamcco/markdown-preview.vim'      " Markdown 预览 
call plug#end() 

" 这几个是挑选的还不错的几个 airline 主题 
" let g:airline_theme="ravenpower" 
" let g:airline_theme="minimalist" 
" let g:airline_theme="kolor" 
" let g:airline_theme="jellybeans" 
" let g:airline_theme="distinguished" 
" let g:airline_theme="base16_google" 
" let g:airline_theme="behelit" 
let g:airline_theme="tomorrow" 

set helplang=cn 
set ambiwidth=double                                         
let g:airline_powerline_fonts = 1 
let g:airline#extensions#tabline#enabled = 1 
let g:airline#extensions#tabline#buffer_nr_show = 1 
" 关闭状态显示空白符号计数 
let g:airline#extensions#whitespace#enabled = 0 
let g:airline#extensions#whitespace#symbol = '!' 
" unicode symbols 
let g:airline_left_sep = '»' 
let g:airline_left_sep = '▶ ' 
let g:airline_right_sep = '«' 
let g:airline_right_sep = '◀ ' 
                                                             
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

" tagbar 配置 
let g:tagbar_width=30 
nnoremap <silent> <F4> :TagbarToggle<CR> 
"将tagbar的开关按键设置为 F4 
let g:tagbar_iconchars = ['+', '-'] 


" nerdtree配置 
nnoremap <F3> :NERDTreeToggle<CR>  
" 开启/关闭nerdtree快捷键 

autocmd StdinReadPre * let s:std_in=1 
autocmd VimEnter * NERDTree | if argc() > 0 || exists("s:std_in") | wincmd p | endif 
autocmd BufEnter * if tabpagenr('$') == 1 && winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree() | quit | endif 
let g:NERDTreeWinSize = 25 "设定 NERDTree 视窗大小 
"设置树的显示图标 
let g:NERDTreeDirArrowExpandable = '+' 
let g:NERDTreeDirArrowCollapsible = '-' 
"let g:NERDTreeShowLineNumbers=1  " 是否显示行号 
"Making it prettier 
let NERDTreeMinimalUI = 1
let NERDTreeDirArrows = 1


" RGB彩色括号
let g:rbpt_colorpairs = [
    \ ['brown',       'RoyalBlue3'],
    \ ['Darkblue',    'SeaGreen3'],
    \ ['darkgray',    'DarkOrchid3'],
    \ ['darkgreen',   'firebrick3'],
    \ ['darkcyan',    'RoyalBlue3'],
    \ ['darkred',     'SeaGreen3'],
    \ ['darkmagenta', 'DarkOrchid3'],
    \ ['brown',       'firebrick3'],
    \ ['gray',        'RoyalBlue3'],
    \ ['black',       'SeaGreen3'],
    \ ['darkmagenta', 'DarkOrchid3'],
    \ ['Darkblue',    'firebrick3'],
    \ ['darkgreen',   'RoyalBlue3'],
    \ ['darkcyan',    'SeaGreen3'],
    \ ['darkred',     'DarkOrchid3'],
    \ ['red',         'firebrick3'],
    \ ]
let g:rbpt_max = 16
let g:rbpt_loadcmd_toggle = 0
au VimEnter * RainbowParenthesesToggle
au Syntax * RainbowParenthesesLoadRound
au Syntax * RainbowParenthesesLoadSquare
au Syntax * RainbowParenthesesLoadBraces


" 设置UTF-8编码
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8

" 解决Backspace无法删除问题
set backspace=2
" 设置鼠标
set mouse=a

" 设置行数显示
" set number
set t_ut= " 防止vim背景颜色错误
set softtabstop=4
syntax on
set t_Co=256
set tabstop=4   "tab长度
imap ( ()<ESC>i
imap () ()<ESC>a

imap [ []<ESC>i
imap [] []<ESC>a

imap {<SPACE> {<SPACE><SPACE>};<ESC><LEFT><LEFT>i
imap {; {<CR><CR>};<ESC>jddkkddkA
imap { {}<ESC>i<CR><CR><ESC>kA<TAB><RIGHT><RIGHT>
imap {} {}<ESC>a

imap < <><ESC>i
imap <<SPACE> <<ESC><RIGHT>r<SPACE>a
imap << <<<ESC><RIGHT>r<SPACE>a<BACKSPACE>
imap <= <=<ESC>a
imap <> <><ESC>a

imap "" ""<ESC>i
imap '' ''<ESC>i

" termdebug 快捷键
nnoremap <F9> :Break<CR>
" 设置断点
nnoremap <F8> :Clear<CR>
" 删除断点
nnoremap <F5> :Run<CR> 
" 运行 
nnoremap <F10> :Step<CR> 
" 逐步运行 
nnoremap <F11> :Next<CR> 
" 逐步运行(进入函数) 
" 
" 
" COC 
" Use <Tab> and <S-Tab> to navigate the completion list 
inoremap <expr> <Tab> pumvisible() ? "\<C-n>" : "\<Tab>" 
inoremap <expr> <S-Tab> pumvisible() ? "\<C-p>" : "\<S-Tab>"