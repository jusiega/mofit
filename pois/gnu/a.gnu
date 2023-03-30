set terminal pngcairo enhanced font "arial,12" fontscale 1.3 size 1200, 900 
set output '../pic/a.png'
set key fixed left top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid
unset parametric
set samples 500
#set title "a" 
#set title  font ",20" textcolor lt -1 norotate
set xlabel "numer iteracji"
set ylabel "a"
unset key
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
NO_ANIMATION = 1
#plot [0:500] 'a.txt' with line
plot  '../output/a.txt' with lines