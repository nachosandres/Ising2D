spins <- as.matrix(read.table("spins.txt"))

spinup <- which(spins == 1, arr.ind=TRUE)
spindown <- which(spins == -1, arr.ind=TRUE)

plot(spinup[,1],spinup[,2],
     xlab="x",ylab="y",main="Spin, T=3",
     pch=15,col=colors()[175],cex=.58,
     xlim=c(0,100),ylim=c(0,100))
points(spindown[,1],spindown[,2],
       pch=15,col=colors()[225],cex=.58)
legend(93.5,105,legend=c('+1',' -1'),
       col=c(colors()[175],colors()[225]), pch=15, cex=.8)


M <- as.matrix(read.table("magnet.txt"))
plot(M,type='l',ylim=c(-1,1),
     xlab="t",ylab="M",main="T=2")

M1p <- as.matrix(read.table("magnet/magnetT1+.txt"))
plot(M1p,type='l',ylim=c(-1,1),
     xlab="t",ylab="<s>",main="T=1",col=2)
M1m <- as.matrix(read.table("magnet/magnetT1-.txt"))
lines(M1m,type='l',ylim=c(-1,1),col=3)
M1d <- as.matrix(read.table("magnet/magnetT1doms.txt"))
lines(M1d,type='l',ylim=c(-1,1),col=4)


M2p <- as.matrix(read.table("magnet/magnetT2+.txt"))
plot(M2p,type='l',ylim=c(-1,1),
     xlab="t",ylab="<s>",main="T=2",col=2)
M2m <- as.matrix(read.table("magnet/magnetT2-.txt"))
lines(M2m,type='l',ylim=c(-1,1),col=3)
M2d <- as.matrix(read.table("magnet/magnetT2doms.txt"))
lines(M2d,type='l',ylim=c(-1,1),col=4)
M215 <- as.matrix(read.table("magnet/magnetT2_15.txt"))
lines(M215,type='l',ylim=c(-1,1),col='green')
M22 <- as.matrix(read.table("magnet/magnetT2_2.txt"))
plot(M22,type='l',ylim=c(-1,1),
     xlab="t",ylab="<s>",main="T~2.3",col='blue')
M225 <- as.matrix(read.table("magnet/magnetT2_25.txt"))
lines(M225,type='l',ylim=c(-1,1),col='red')



M235 <- as.matrix(read.table("magnet/magnetT2_35.txt"))
lines(M235,type='l',ylim=c(-1,1),col="orange")
M24 <- as.matrix(read.table("magnet/magnetT2_4.txt"))
lines(M24,type='l',ylim=c(-1,1),col="purple")

legend(14000,-0.4,legend=c('T=2.15','T=2.2','T=2.25','T=2.35','T=2.4'),
       col=c('green','blue','red','orange','purple'), lwd=2)

M25 <- as.matrix(read.table("magnet/magnetT2_5.txt"))
plot(M25,type='l',xlab="t",ylab="<s>",main="T>2.3",ylim=c(-1,1),col="purple")
M3 <- as.matrix(read.table("magnet/magnetT3.txt"))
lines(M3,type='l',ylim=c(-1,1),col="orange")
legend(15000,0.7,legend=c('T=2.5','T=3'),
       col=c('purple','orange'), lwd=2)
M[10000]

Mt <- as.matrix(read.table("meanMvsT.txt"))
plot(Mt[,1],Mt[,2],ylim=c(-1,1))
abline(h=0)

M231 <- as.matrix(read.table("magnet/magnetT2_3_1.txt"))
plot(M231,type='l',ylim=c(-1,1),
     xlab="t",ylab="<s>",main="T=2.3")
M232 <- as.matrix(read.table("magnet/magnetT2_3_2.txt"))
lines(M232,type='l',ylim=c(-1,1),col='red')
M233 <- as.matrix(read.table("magnet/magnetT2_3_3.txt"))
lines(M233,type='l',ylim=c(-1,1),col='green')
M234 <- as.matrix(read.table("magnet/magnetT2_3_4.txt"))
lines(M234,type='l',ylim=c(-1,1),col='blue')
abline(h=1)
abline(h=-1)

library(Hmisc)
Mmeant <- as.matrix(read.table("Mmean.txt"))
plot(Mmeant[,1],Mmeant[,2],ylim=c(-1,1),pch=20,cex=.5,
     xlab="T",ylab="M",xaxp=c(1,3,8))
abline(h=0)
abline(h=1)
abline(h=-1)
abline(v=2.3)
# errbar(years,datyear,datyear+erryear,datyear-erryear,xlab="Año",ylab="Fracción de noches perdidas")
# title(main="Variación interanual")
# mtext("Ajuste a constante")
errbar(Mmeant[,1],Mmeant[,2],Mmeant[,2]+Mmeant[,3],Mmeant[,2]-Mmeant[,3],
       xlab="T",ylab="<s>",pch=20,cex=.5,col="black",errbar.col="orange")
title("Magnetización promedio")
points(Mmeant[,1],Mmeant[,2],pch=20,cex=.5,col="black")
