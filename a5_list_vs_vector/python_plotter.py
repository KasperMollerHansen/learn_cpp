#%%
import os
import pandas as pd
import plotly.graph_objects as go
import numpy as np


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

files_no_optimizations = {
    "vector": "vector_benchmark_no_optimizations.csv",
    "list": "list_benchmark_no_optimizations.csv",
    "set": "set_benchmark_no_optimizations.csv"
}


vector_data = pd.read_csv(os.path.join(data_dir, files["vector"]))
list_data = pd.read_csv(os.path.join(data_dir, files["list"]))
set_data = pd.read_csv(os.path.join(data_dir, files["set"]))

# Load no optimizations data
vector_data_noopt = pd.read_csv(os.path.join(data_dir, files_no_optimizations["vector"]))
list_data_noopt = pd.read_csv(os.path.join(data_dir, files_no_optimizations["list"]))
set_data_noopt = pd.read_csv(os.path.join(data_dir, files_no_optimizations["set"]))
#%%

# Insert time plot
fig_insert = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data, list_data, set_data]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_insert.add_trace(go.Scatter(
        x=grouped.index, y=grouped["insert_time_ms"],
        mode='lines+markers', name=label
    ))
fig_insert.update_layout(
    title="<b>Insert Times</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
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
    title="<b>Remove Times</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
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
    title="<b>Total Times (Insert + Remove)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_total.show()
fig_total.write_image(os.path.join(plot_dir, "total_times_plot.png"))


# Insert time plot (no optimizations)
fig_insert_noopt = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_noopt, list_data_noopt, set_data_noopt]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_insert_noopt.add_trace(go.Scatter(
        x=grouped.index, y=grouped["insert_time_ms"],
        mode='lines+markers', name=label
    ))
fig_insert_noopt.update_layout(
    title="<b>Insert Times (No Optimizations)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_insert_noopt.show()
fig_insert_noopt.write_image(os.path.join(plot_dir, "insert_times_plot_noopt.png"))

# Remove time plot (no optimizations)
fig_remove_noopt = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_noopt, list_data_noopt, set_data_noopt]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_remove_noopt.add_trace(go.Scatter(
        x=grouped.index, y=grouped["remove_time_ms"],
        mode='lines+markers', name=label
    ))
fig_remove_noopt.update_layout(
    title="<b>Remove Times (No Optimizations)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_remove_noopt.show()
fig_remove_noopt.write_image(os.path.join(plot_dir, "remove_times_plot_noopt.png"))

# Insert + Remove time plot (no optimizations)
fig_total_noopt = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_noopt, list_data_noopt, set_data_noopt]):
    grouped = df.groupby("N").mean(numeric_only=True)
    total_time = grouped["insert_time_ms"] + grouped["remove_time_ms"]
    fig_total_noopt.add_trace(go.Scatter(
        x=grouped.index, y=total_time,
        mode='lines+markers', name=label
    ))
fig_total_noopt.update_layout(
    title="<b>Total Times (Insert + Remove, No Optimizations)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_total_noopt.show()
fig_total_noopt.write_image(os.path.join(plot_dir, "total_times_plot_noopt.png"))

#%%
def get_row_colors(n_rows):
    colors = []
    for i in range(n_rows):
        if i % 2 == 0:
            colors.append("#fdfdfd")  # near white
        else:
            colors.append("#eef2fa")  # light blue gradient
    return colors

def make_pivot_table(data_dict):
    summary = []
    for label, df in data_dict.items():
        grouped = df.groupby("N").mean(numeric_only=True)
        for n, row in grouped.iterrows():
            summary.append({
                "N": n,
                "Container": label,
                "Insert Time (ms)": np.round(row["insert_time_ms"], 4),
                "Remove Time (ms)": np.round(row["remove_time_ms"], 4)
            })
    summary_df = pd.DataFrame(summary)
    pivot = summary_df.pivot(index="N", columns="Container")[["Insert Time (ms)", "Remove Time (ms)"]]
    pivot.columns = [f"{container} {metric}" for metric, container in pivot.columns]
    pivot = pivot.reset_index()

    # Reorder columns: N, vector Insert, list Insert, set Insert, set Remove, vector Remove, list Remove
    desired_order = ["N"]
    insert_cols = [col for col in pivot.columns if "Insert Time" in col]
    remove_cols = [col for col in pivot.columns if "Remove Time" in col]
    vector_inserts = [col for col in insert_cols if col.startswith("vector ")]
    list_inserts = [col for col in insert_cols if col.startswith("list ")]
    set_insert = [col for col in insert_cols if col.startswith("set ")]
    vector_removes = [col for col in remove_cols if col.startswith("vector ")]
    list_removes = [col for col in remove_cols if col.startswith("list ")]
    set_remove = [col for col in remove_cols if col.startswith("set ")]

    # New order: N, vector_insert, list_insert, set_insert, set_remove, vector_remove, list_remove
    desired_order += vector_inserts + vector_removes + list_inserts + list_removes + set_insert + set_remove
    desired_order = [col for col in desired_order if col in pivot.columns]
    pivot = pivot[desired_order]
    return pivot

# Optimized data
pivot_opt = make_pivot_table({
    "vector": vector_data,
    "list": list_data,
    "set": set_data
})
row_colors_opt = get_row_colors(len(pivot_opt))
fig_pivot_opt = go.Figure(data=[go.Table(
    columnwidth=[60] + [120] * (len(pivot_opt.columns) - 1),
    header=dict(
        values=[f"<b>{col}</b>" for col in pivot_opt.columns],
        fill_color='#2a3f5f',
        font=dict(color='white', size=15, family='Arial Black'),
        align='center',
        line_color='white',
        height=36
    ),
    cells=dict(
        values=[pivot_opt[col] for col in pivot_opt.columns],
        fill=dict(color=[row_colors_opt]),
        align='center',
        font=dict(color='black', size=14, family='Helvetica'),
        line_color='white',
        height=30,
    )
)])
fig_pivot_opt.update_layout(
    title=dict(
        text="<b>Mean Insert & Remove Times (Optimized)</b><br><span style='font-size:14px;'>Lower is better</span>",
        x=0.5,
        xanchor="center",
        font=dict(size=20, family="Arial Black")
    ),
    margin=dict(l=20, r=20, t=80, b=20),
    width=1100,
    height=550,
    paper_bgcolor="#f8f9fc",
)
fig_pivot_opt.show()
fig_pivot_opt.write_image(os.path.join(plot_dir, "pivot_table_optimized.png"))

# No optimizations data
pivot_noopt = make_pivot_table({
    "vector": vector_data_noopt,
    "list": list_data_noopt,
    "set": set_data_noopt
})
row_colors_noopt = get_row_colors(len(pivot_noopt))
fig_pivot_noopt = go.Figure(data=[go.Table(
    columnwidth=[60] + [120] * (len(pivot_noopt.columns) - 1),
    header=dict(
        values=[f"<b>{col}</b>" for col in pivot_noopt.columns],
        fill_color='#2a3f5f',
        font=dict(color='white', size=15, family='Arial Black'),
        align='center',
        line_color='white',
        height=36
    ),
    cells=dict(
        values=[pivot_noopt[col] for col in pivot_noopt.columns],
        fill=dict(color=[row_colors_noopt]),
        align='center',
        font=dict(color='black', size=14, family='Helvetica'),
        line_color='white',
        height=30,
    )
)])
fig_pivot_noopt.update_layout(
    title=dict(
        text="<b>Mean Insert & Remove Times (No Optimizations)</b><br><span style='font-size:14px;'>Lower is better</span>",
        x=0.5,
        xanchor="center",
        font=dict(size=20, family="Arial Black")
    ),
    margin=dict(l=20, r=20, t=80, b=20),
    width=1100,
    height=550,
    paper_bgcolor="#f8f9fc",
)
fig_pivot_noopt.show()
fig_pivot_noopt.write_image(os.path.join(plot_dir, "pivot_table_noopt.png"))