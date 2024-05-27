# Euler Discretization

Recall the formula of a stock price following Geometric Brownian Motion (GBM) under risk-neutral considerations:

$$\frac{dS_t}{S_t} = rdt + \sigma dw_t $$

where $w_t$ is a standard Brownian motion with the following distribution:

$$w_t \sim N(0, \Delta t) $$

where $\Delta t$ is the length of the time increment. The expression above can be reformulated to express the change in stock price in one time step in the following manner:

$$dS_t = rS_tdt + \sigma S_tdw_t $$

therefore the stock price at the next time step can be expressed as:

$$S_t + dS_t =  S_t + \int_{t}^{t + \Delta t}{S_ud_u} + \sigma \int_{t}^{t + \Delta t}{S_udw_u} $$

To simplify this expression, we will use Euler discretization. We make the assumption that the time steps ($\Delta t$) are small and therefore the stock price shouldn't change much within these brief time intervals. We make a first order approximation and fix the left endpoint t giving us:

$$\int_{t}^{t + \Delta t}{S_ud_u} \approx S_t \int_{t}^{t + \Delta t}{d_u} = S_t \Delta t$$

$$\int_{t}^{t + \Delta t}{S_udw_u} \approx S_t \int_{t}^{t + \Delta t}{dw_u} = S_t(w_{t+\Delta t} -w_t)$$

putting everything together we have:
$$S_t + dS_t = S_t + rS_t\Delta t + \sigma S_t \Delta w_t $$

# Monte Carlo Simulation

Recall the fair price of a European call option should adhere to the following formula:

$$f(S_T) = e^{-r T} (S_T - K)^+$$
and subsequently for a European put option:

$$f(S_T) = e^{-r T} (K - S_T)^+$$

where K is the strike price and $S_T$ is the stock price at the option's maturity. Given N different simulations of stock price evolution paths following Euler discretization methodologies, the fair price should be the average or expected value of the fair price given each simulation's terminal node stock price:

$$ \hat{V_N}= \frac{1}{N} \times \sum^N_{i=1} f\bigg(S_T(i)\bigg)  $$

note that by using Euler discretization and simplifying the simulation process, we introduced bias into the Monte Carlo simulation procedure. 

# Heston Model

Although it simplifies the simulation process, in reality, a stock's volatility doesn't remain constant. The Heston model allows us to account for this time varying volatility in the following manner:

$$dS_t = rS_tdt + \sqrt{v_t} S_t dw_t^1 $$

$$dv_t = k(\theta - v_t)dt + \sigma_v \sqrt{v_t }dw_t^2 $$
where 

- $v_0$ is the starting stock variance
- $\theta$ is the long-term average variance in which the variance process reverts to
- $k$ is the rate of reversion
- $\sigma_v$ is the volatility of the stock price's volatility

Note that the variance process and the stock price process have different underlying Brownian motions with some correlation factor $\rho$
