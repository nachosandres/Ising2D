spins <- as.matrix(read.table("spins.txt"))

spinup <- which(spins == 1, arr.ind=TRUE)
spindown <- which(spins == -1, arr.ind=TRUE)

plot(spinup[,1],spinup[,2],
     xlab="x",ylab="y",main="Spin",
     pch=15,col=colors()[175],cex=.55)
points(spindown[,1],spindown[,2],
       pch=15,col=colors()[225],cex=.55)
legend(93.5,105,legend=c('+1',' -1'),
       col=c(colors()[175],colors()[225]), pch=15, cex=.8)


M <- as.matrix(read.table("magnet.txt"))
plot(M,type='l',ylim=c(-1,1))
