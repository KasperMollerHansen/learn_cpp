#%%
import os
import pandas as pd
import plotly.graph_objects as go

# Get current working directory
current_dir = os.path.dirname(os.path.abspath(__file__))
data_dir = os.path.join(current_dir, "output_data/")
plot_dir = os.path.join(current_dir, "output_plots/")
os.makedirs(plot_dir, exist_ok=True)

files = {
    "vector": "vector_benchmark.csv",
    "list": "list_benchmark.csv",
    "set": "set_benchmark.csv"
}

vector_data = pd.read_csv(os.path.join(data_dir, files["vector"]))
list_data = pd.read_csv(os.path.join(data_dir, files["list"]))
set_data = pd.read_csv(os.path.join(data_dir, files["set"]))

# Insert time plot
fig_insert = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data, list_data, set_data]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_insert.add_trace(go.Scatter(
        x=grouped.index, y=grouped["insert_time_ms"],
        mode='lines+markers', name=label
    ))
fig_insert.update_layout(
    title="Insert Times for Vector, List, and Set",
    xaxis_title="N",
    yaxis_title="Insert Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_insert.show()
fig_insert.write_image(os.path.join(plot_dir, "insert_times_plot.png"))

# Remove time plot
fig_remove = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data, list_data, set_data]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_remove.add_trace(go.Scatter(
        x=grouped.index, y=grouped["remove_time_ms"],
        mode='lines+markers', name=label
    ))
fig_remove.update_layout(
    title="Remove Times for Vector, List, and Set",
    xaxis_title="N",
    yaxis_title="Remove Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_remove.show()
fig_remove.write_image(os.path.join(plot_dir, "remove_times_plot.png"))

# Insert + Remove time plot
fig_total = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data, list_data, set_data]):
    grouped = df.groupby("N").mean(numeric_only=True)
    total_time = grouped["insert_time_ms"] + grouped["remove_time_ms"]
    fig_total.add_trace(go.Scatter(
        x=grouped.index, y=total_time,
        mode='lines+markers', name=label
    ))
fig_total.update_layout(
    title="Total (Insert + Remove) Times for Vector, List, and Set",
    xaxis_title="N",
    yaxis_title="Total Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_total.show()
fig_total.write_image(os.path.join(plot_dir, "total_times_plot.png"))
