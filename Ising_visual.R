spins <- as.matrix(read.table("spins.txt"))

spinup <- which(spins == 1, arr.ind=TRUE)
spindown <- which(spins == -1, arr.ind=TRUE)

plot(spinup[,1],spinup[,2],
     xlab="x",ylab="y",main="Spin",
     pch=15,col=colors()[175],cex=.57)
points(spindown[,1],spindown[,2],
       pch=15,col=colors()[225],cex=.57)
legend(93.5,105,legend=c('+1',' -1'),
       col=c(colors()[175],colors()[225]), pch=15, cex=.8)


M <- as.matrix(read.table("magnet.txt"))
plot(M,type='l',ylim=c(-1,1))
M[10000]

Mt <- as.matrix(read.table("meanMvsT.txt"))
plot(Mt[,1],Mt[,2],ylim=c(-1,1))
abline(h=0)
