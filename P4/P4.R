# install.packages('tuneR', dep=TRUE)
# install.packages('seewave', dep=TRUE)

# Librerias
library(tuneR)
library(seewave)

# Paths
setwd("/home/mono/UGR/ugr-cs-1920/PDIH/src/P4/")
setWavPlayer('/usr/bin/mpv')

# Lectura de ficheros de audio
perro <- readWave('audio/perro.wav')
oveja <- readWave('audio/oveja.wav')
listen(perro)
listen(oveja)

# Forma de onda de ambos audios
plot(extractWave(perro, from = 0, to = length(perro)))
plot(extractWave(oveja, from = 0, to = length(oveja)))

# Headers
str(perro)
str(oveja)

# Mezcla de sonidos
perroCut <- cutw(perro, to=2.2, output="Wave")
mezcla <- pastew(perroCut, oveja, at = "end", output="Wave")
plot(extractWave(mezcla, from = 0, to = length(mezcla)))
listen(mezcla)

# Filtro de frecuencia
mezcla2 <- bwfilter(mezcla, f=mezcla@samp.rate, from=10000, to=20000, output="Wave")
plot(extractWave(mezcla2, from = 0, to = length(mezcla2)))
listen(mezcla2)

# Escrituda de fichero WAV
writeWave(mezcla2, "audio/mezcla.wav")

# Nuevo audio
intro <- readMP3("audio/intro20th.mp3")
plot(extractWave(intro, from = 0, to = length(intro)))
listen(intro)

# Eco
echoLeft <- echo(intro, f=intro@samp.rate, channel=1, amp = c(0.6, 0.4, 0.2), delay = c(1, 2, 3), output="Wave")
echoRight <- echo(intro, f=intro@samp.rate, channel=2, amp = c(0.6, 0.4, 0.2), delay = c(1, 2, 3), output="Wave")

# Audio del revés
revLeft <- revw(echoLeft, f = echoLeft@samp.rate, output = "Wave")
revRight <- revw(echoRight, f = echoRight@samp.rate, output = "Wave")

# Audio final
introRev <- normalize(stereo(revLeft, revRight), "16")
plot(extractWave(introRev, from = 0, to = length(introRev)))
listen(introRev)

# Escrituda de fichero WAV
writeWave(introRev, "audio/alreves.wav")
