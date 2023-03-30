set terminal pngcairo enhanced font "arial,12" fontscale 1.3 size 1200, 900 
set output '../pic/delta500.png'
set key fixed left top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid
unset parametric
set samples 10000000
set encoding utf8
set title "δ(x,y) po 500 iteracjach" 
#set title  font ",20" textcolor lt -1 norotate
set xlabel "x"
set ylabel "y"
unset key
set tics front
set grid front 
set grid linetype 1 lc rgb "black" lw 0.2137
set xrange [ -31 : 31] noreverse nowriteback
set x2range [ * : * ] noreverse writeback
set yrange [ -31 : 31 ] noreverse nowriteback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ -0.1 : 0.1 ] noreverse nowriteback
set rrange [ * : * ] noreverse writeback
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
NO_ANIMATION = 1
#plot [0:500] 'a.txt' with line
plot  '../output/delta500.txt' with image 