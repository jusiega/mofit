set terminal pngcairo enhanced font "arial,12" fontscale 1.0 size 800, 600 
set output '../pic/u.png'
set autoscale xfix
set autoscale yfix
set autoscale cbfix
set pm3d map
splot '../output/u100.txt' matrix nonuniform notitle