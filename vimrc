"nmap zcc :mapclear!<CR>
nmap zso :source C:\_vimrc <CR>

nmap ,p "0p
nmap ,P "0P
imap z,p <Esc>"0pa
imap z,P <Esc>"0Pa
:nmap z, vi)
:nmap z. vi}
:nmap z) vi)
:nmap z} vi}
:nmap z> vit
:nmap c> cit
:nmap z" vi"
:nmap zcc ci"
:nmap zaa ca"
:nmap zxx ci]
:vmap <Esc> <Esc><Esc><Esc>
:imap jj <Esc>
:nmap <BS> a<BS>
:nmap zh ^
:nmap hh ^
:imap zh <Esc>^i
:nmap zl $
:nmap ll $
:imap zl <End>
:nmap zt zt2k2j
:nmap hc ^C
:nmap zb bcw
:vmap zb <Esc>bcw
:imap zd <Esc>dd
nmap j gj
nmap k gk
nmap qq ZQ
nmap zq :wq<CR>
nmap <A-u> :redo<CR>
:imap <C-x> <Esc>dd
:imap <C-a> <Esc>ma<CR>ggVG
" map C :set rnu!<CR>
" insert single char
:map ,i i?<Esc>r
" append single char
:map ,a a?<Esc>r
