call plug#begin('~/.config/nvim/plugged')
Plug 'mg979/vim-xtabline'
Plug 'bling/vim-airline'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'vim-airline/vim-airline-themes'
Plug 'jiangmiao/auto-pairs' 	
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

" 设置UTF-8编码
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
" 设置行数显示
set number
set t_ut= " 防止vim背景颜色错误
set softtabstop=4
set t_Co=256
set tabstop=4	"tab长度
set shiftwidth=4   " 缩进长度

"===========================================
"coc.nvim 配置
"===========================================
"
" TAB选择 
" Use tab for trigger completion with characters ahead and navigate.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ CheckBackspace() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"
function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

" Highlight the symbol and its references when holding the cursor.
autocmd CursorHold * silent call CocActionAsync('highlight')

" coc加载
set updatetime=100

" coc-translator


" explorer 快捷
nmap <F4> <Cmd>CocCommand explorer<CR>
