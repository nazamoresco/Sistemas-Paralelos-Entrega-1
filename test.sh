# Cambiar cuando sea por columna

N=2
A="1,2,1,2"
B="2,1,2,1"
T="0,0,1,1"
M="1.570796327,0,1.047197551,4.71238898"

echo "1" "2" "1" "2" "2" "1" "2" "1" "0" "0" "1" "1" "1.570796327" "0" "1.047197551" "4.71238898"| ./ejer2 $N
# echo $A | ./ejer2 $N
# echo $RESULTADO

# CALCULOS

# Calculo de R
# (1 - 0) * (1 - cos(1,570796327)) + 0 * sin(1,570796327) = 1
# (1 - 0) * (1 - cos(0)) + 0 * sin(0)                     = 0
# (1 - 1) * (1 - cos(1,047197551)) + 1 * sin(1,047197551) = 0.86602540368
# (1 - 1) * (1 - cos(4,71238898)) + 1 * sin(4,71238898)   = -1

# A + B = 3,3,3,3

# AVERAGE =  0.86602540368 / 4 = 0,216506351
# R(A + B)

# R1,1 = 3 = 1 * 3 + 0 * 3
# R2,1 = 3 = 1 * 3 + 0 * 3
# R1,2 = -0.401925 = 0.86602540368  * 3 +  -1  * 3
# R2,2 = -0.401925 =  0.86602540368  * 3 +  -1  * 3


# AVERAGE * R(A + B) = 0,649519053, 0,649519053, −0,087019315, −0,087019315

# 𝑇 + AVERAGE * R(A + B) = 0,649519053, 0,649519053,0,912980685,0,912980685
