
$$I = \begin{pmatrix}
  {1} & {0} & {0} & {0} \\
  {0} & {1} & {0} & {0} \\
  {0} & {0} & {1} & {0} \\
  {0} & {0} & {0} & {1} 
 \end{pmatrix}$$
 
#
 
 $$R{x} = 
 \begin{pmatrix}
  {1} & {0} & {0} & {0} \\
  {0} & cos{\theta} & sin{\theta} & {0} \\
  {0} & -sin{\theta} & cos{\theta} & {0} \\
  {0} & {0} & {0} & {1}
 \end{pmatrix}
 { , }
 R{y} = 
  \begin{pmatrix}
  cos {\theta} & {0} & -sin{\theta} & {0} \\
  {0} & {1} & {0} & {0} \\
  sin{\theta} & {0} & cos{\theta} & {0} \\
  {0} & {0} & {0} & {1}
 \end{pmatrix}
 { , }
 R{z} = 
 \begin{pmatrix}
  cos{\theta} & sin{\theta} &{0} &{0}\\
  -sin{\theta} & cos{\theta} &{0} &{0}\\
  {0} & {0} & {1} & {0} \\
  {0} & {0} & {0} & {1}
 \end{pmatrix}$$
 
 #
 
 $$R = R{z}R{y}R{x} =
 \begin{pmatrix}
  R_{x} & R_{y} & R_{z} & {0} \\
  U_{x} & U_{y} & U_{z} & {0} \\
  F_{x} & F_{y} & F_{z} & {0} \\
  {0} & {0} & {0} & {1}
 \end{pmatrix}
 ,
 T =
 \begin{pmatrix}
  {1} & {0} & {0} & {0} \\
  {0} & {1} & {0} & {0} \\
  {0} & {0} & {1} & {0} \\
  T_{x} & T_{y} & T_{z} & {1}
 \end{pmatrix}$$
 
#
$$I = (RT)V \quad , V = (RT)^{-1}I $$
#
$$V^{-1} = M = RT =
 \begin{pmatrix}
  R_{x} & R_{y} & R_{z} & {0} \\
  U_{x} & U_{y} & U_{z} & {0} \\
  F_{x} & F_{y} & F_{z} & {0} \\
  T_{x} & T_{y} & T_{z} & {1}
 \end{pmatrix}$$
