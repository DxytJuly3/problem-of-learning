" YouCompleteMe

set runtimepath+=~/.vim/bundle/YouCompleteMe

let g:ycm_collect_identifiers_from_tags_files = 1      " 开启 YCM 基于标签引擎

let g:ycm_collect_identifiers_from_comments_and_strings = 1 " 注释与字符串中的内容也用于补全

let g:syntastic_ignore_files=[".*\.py$"]

let g:ycm_seed_identifiers_with_syntax = 1         " 语法关键字补全

let g:ycm_complete_in_comments = 1

let g:ycm_confirm_extra_conf = 0

let g:ycm_key_list_select_completion = ['<c-n>', '<Down>'] " 映射按键, 没有这个会拦截掉tab, 导致其他插件的tab不能用.

let g:ycm_key_list_previous_completion = ['<c-p>', '<Up>']

let g:ycm_complete_in_comments = 1             " 在注释输入中也能补全

let g:ycm_complete_in_strings = 1              " 在字符串输入中也能补全

let g:ycm_collect_identifiers_from_comments_and_strings = 1 " 注释和字符串中的文字也会被收入补全

let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'

let g:ycm_show_diagnostics_ui = 0              " 禁用语法检查

inoremap <expr> <CR> pumvisible() ? "\<C-y>" : "\<CR>" |      " 回车即选中当前项

nnoremap <c-j> :YcmCompleter GoToDefinitionElseDeclaration<CR>|   " 跳转到定义处

"let g:ycm_min_num_of_chars_for_completion=2         " 从第2个键入字符就开始罗列匹配项

" 设置不兼容vi

set nocompatible

filetype off

" 设置包括vundle和初始化相关的runtime path

set rtp+=~/.vim/bundle/Vundle.vim

" 插件的初始化

call vundle#begin()

Plugin 'Valloric/YouCompleteMe'

call vundle#end()

 

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

"键盘命令

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

 

nmap <leader>w :w!<cr>

nmap <leader>f :find<cr>

 

" 映射全选+复制 ctrl+a

map <C-A> ggVGY

map! <C-A> <Esc>ggVGY

map <F12> gg=G

" 选中状态下 Ctrl+c 复制

vmap <C-c> "+y

"去空行

nnoremap <F2> :g/^\s*$/d<CR>

"比较文件

nnoremap <C-F2> :vert diffsplit

"新建标签

map <M-F2> :tabnew<CR>

"列出当前目录文件

map <F3> :tabnew .<CR>

"打开树状文件目录

map <C-F3> \be

"C，C++ 按F5编译运行

map <F5> :call CompileRunGcc()<CR>

func! CompileRunGcc()

  exec "w"

  if &filetype == 'c'

​    exec "!g++ % -o %<"

​    exec "! ./%<"

  elseif &filetype == 'cpp'

​    exec "!g++ % -o %<"

​    exec "! ./%<"

  elseif &filetype == 'java'

​    exec "!javac %"

​    exec "!java %<"

  elseif &filetype == 'sh'

​    :!./%

  endif

endfunc

"C,C++的调试

map <F10> :call Rungdb()<CR>

func! Rungdb()

  exec "w"

  exec "!g++ % -g -o %<"
	exec "!gdb ./%<"
endfunc



"在 调用 call plug#begin('~/.config/nvim/plugged') 之前 设置plug_url_format即可
let g:plug_url_format='https://git::@hub.fastgit.xyz/%s.git'
call plug#begin('~/.vim/plugged')
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'jiangmiao/auto-pairs'     "自动补全
Plug 'scrooloose/nerdtree'      "树形目录
Plug 'Xuyuanp/nerdtree-git-plugin'      "NerdTree 显示 git 状态
Plug 'junegunn/vim-easy-align'      "对齐插件，强迫症福音
Plug 'iamcco/markdown-preview.vim'      "Markdown 预览
Plug 'junegunn/vim-slash'       "优化搜索，移动清除搜索高亮
Plug 'gorodinskiy/vim-coloresque'       "颜色预览
Plug 'tpope/vim-surround'       "自动增加、替换配对符
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
set nu                 " 行号 
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