import numpy as np
import plotly.graph_objects as go


N = np.array([10, 100, 1000, 
              10000, 100000, 1000000, 
              5000000, 10000000, 20000000, 
              50000000, 70000000, 100000000])
t_c_plus_plus = np.array([0, 0, 0, 
                          0.001, 0.008, 0.074, 
                          0.353, 0.7, 1.399, 
                          3.464, 4.907, 6.98])
t_python = np.array([0, 0, 0, 
                     0.001, 0.016, 0.154, 
                     0.750805, 1.621, 3.02, 
                     8.28, 11.938, 15.490])

fig = go.Figure()

title = "Исследование зависимости времени выполнения от количество повторений в цикле"
x_label = "N, количесто повторений"
y_label = "t, с"

fig.update_layout(
      title=dict(
          text=title,
          x=0.5,
          font=dict(size=16)
      ),
      xaxis=dict(
          title=x_label,
          type="log", 
          gridcolor='lightgray',
          gridwidth=1,
      ),
      yaxis=dict(
          title=y_label,
          gridcolor='lightgray',
          gridwidth=1,
      ),
      legend=dict(
          yanchor="top",
          y=0.99,
          xanchor="left",
          x=0.01,
          bgcolor='rgba(255, 255, 255, 0.8)',
          bordercolor='black',
          borderwidth=1
      ),
      plot_bgcolor='#fffbd9',
      hovermode='x unified',
      width=1000,
      height=600
)

fig.update_xaxes(showgrid=True, gridwidth=1, gridcolor='lightgray')
fig.update_yaxes(showgrid=True, gridwidth=1, gridcolor='lightgray')

fig.add_trace(go.Scatter(
        x=N,
        y=t_c_plus_plus,
        mode='lines+markers',
        name="С++",
        line=dict(color="#ff82d5", width=2),
        marker=dict(size=4),
        hovertemplate='N = %{x}<br>  t = %{y:.2e}<extra></extra>'
))

fig.add_trace(go.Scatter(
        x=N,
        y=t_python,
        mode='lines+markers',
        name="Python",
        line=dict(color="#54d7ff", width=2),
        marker=dict(size=4),
        hovertemplate='N = %{x}<br>  t = %{y:.2e}<extra></extra>'
))

fig.write_image("./lab_02/doc/graph.png")