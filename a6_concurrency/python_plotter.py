#%%
import plotly.graph_objects as go
import pandas as pd
import os

# Get the directory where this script is located
script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, "output_plots")
os.makedirs(plot_dir, exist_ok=True)

# --- Serial vs Parallel ---
df = pd.read_csv(os.path.join(script_dir, "output_data/results_serial_vs_parallel.csv"), comment='/')
fig1 = go.Figure()
fig1.add_trace(go.Scatter(x=df['N'], y=df['serial'], mode='lines+markers', name='Serial'))
fig1.add_trace(go.Scatter(x=df['N'], y=df['parallel'], mode='lines+markers', name='Parallel'))
fig1.add_trace(go.Scatter(x=df['N'], y=df['parallel_ready'], mode='lines+markers', name='Parallel Ready'))
fig1.update_layout(
    title="<b>Serial vs Parallel vs Parallel Ready</b><br><span style='font-size:14px'>Mean of 5 runs, varying N</span>",
    xaxis_title="<b>Array Size N</b>",
    yaxis_title="<b>Time (ms)</b>",
    xaxis_type="log",
    yaxis_type="log"
)
fig1.write_image(os.path.join(plot_dir, "serial_vs_parallel.png"))
fig1.show()

# --- Thread Scaling (Small) ---
df_small = pd.read_csv(os.path.join(script_dir, "output_data/results_thread_scaling_small.csv"), comment='/')
fig2 = go.Figure()
fig2.add_trace(go.Scatter(x=df_small['threads'], y=df_small['parallel'], mode='lines+markers', name='Parallel'))
fig2.add_trace(go.Scatter(x=df_small['threads'], y=df_small['parallel_ready'], mode='lines+markers', name='Parallel Ready'))
fig2.update_layout(
    title="<b>Thread Scaling (Small N)</b><br><span style='font-size:14px'>Mean of 5 runs, N = 1,000,000</span>",
    xaxis_title="<b>Number of Threads</b>",
    yaxis_title="<b>Time (ms)</b>",
    xaxis_type="log",
    yaxis_type="log"
)
fig2.write_image(os.path.join(plot_dir, "thread_scaling_small.png"))
fig2.show()

# --- Thread Scaling (Large) ---
df_large = pd.read_csv(os.path.join(script_dir, "output_data/results_thread_scaling_large.csv"), comment='/')
fig3 = go.Figure()
fig3.add_trace(go.Scatter(x=df_large['threads'], y=df_large['parallel'], mode='lines+markers', name='Parallel'))
fig3.add_trace(go.Scatter(x=df_large['threads'], y=df_large['parallel_ready'], mode='lines+markers', name='Parallel Ready'))
fig3.update_layout(
    title="<b>Thread Scaling (Large N)</b><br><span style='font-size:14px'>Mean of 5 runs, N = 1,000,000,000</span>",
    xaxis_title="<b>Number of Threads</b>",
    yaxis_title="<b>Time (ms)</b>",
    xaxis_type="log",
    yaxis_type="log"
)
fig3.write_image(os.path.join(plot_dir, "thread_scaling_large.png"))
fig3.show()
#%%
def save_table(df, title, filename):
    fig = go.Figure(data=[go.Table(
        header=dict(values=[f"<b>{col}</b>" for col in df.columns],
                    fill_color='paleturquoise',
                    align='center'),
        cells=dict(values=[df[col] for col in df.columns],
                   fill_color='lavender',
                   align='center'))
    ])
    fig.update_layout(title=title)
    fig.write_image(os.path.join(plot_dir, filename))

# --- Serial vs Parallel Table ---
df = pd.read_csv(os.path.join(script_dir, "output_data/results_serial_vs_parallel.csv"), comment='/')
save_table(df, "Serial vs Parallel vs Parallel Ready (Raw Data)", "serial_vs_parallel_table.png")

# --- Thread Scaling (Small) Table ---
df_small = pd.read_csv(os.path.join(script_dir, "output_data/results_thread_scaling_small.csv"), comment='/')
save_table(df_small, "Thread Scaling (Small N) (Raw Data)", "thread_scaling_small_table.png")

# --- Thread Scaling (Large) Table ---
df_large = pd.read_csv(os.path.join(script_dir, "output_data/results_thread_scaling_large.csv"), comment='/')
save_table(df_large, "Thread Scaling (Large N) (Raw Data)", "thread_scaling_large_table.png")
