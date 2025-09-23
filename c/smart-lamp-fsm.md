# 智能台灯状态机图

```mermaid
stateDiagram-v2
    [*] --> OFF
    
    OFF --> ON: SHORT_PRESS
    OFF --> NIGHT: LONG_PRESS
    OFF --> BOOST: DOUBLE_TAP
    
    ON --> OFF: SHORT_PRESS
    ON --> NIGHT: LONG_PRESS
    ON --> BOOST: DOUBLE_TAP
    ON --> OFF: IDLE_TIMEOUT
    
    NIGHT --> OFF: SHORT_PRESS
    NIGHT --> ON: LONG_PRESS
    NIGHT --> BOOST: DOUBLE_TAP
    NIGHT --> OFF: IDLE_TIMEOUT
    
    BOOST --> OFF: SHORT_PRESS
    BOOST --> NIGHT: LONG_PRESS
    BOOST --> BOOST: DOUBLE_TAP (reset timer)
    BOOST --> ON: TICK_1S (timer==0)
