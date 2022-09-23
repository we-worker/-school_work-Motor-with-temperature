# -school_work-Motor-with-temperature

## 设计思路

- 风扇pwm-->tim1-pwm模式-ccr2

- 加热pwm-->tim1-pwm模式-ccr1

  

  #### 系统时钟

  48M

  #### tim1配置

  - ​	分频48
  - 计数上限1000

  #### 测温
  - 热敏电阻 R(Pt100)=100+0.3851*Temp(℃) Ω
  - 模拟量输出电压Vt=V(ms) * 10 R(Pt100) / [ R(Pt100) + 1KΩ]