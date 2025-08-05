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

files_large = {
    "vector": "vector_benchmark_large.csv",
    "list": "list_benchmark_large.csv",
    "set": "set_benchmark_large.csv"
}

vector_data_large = pd.read_csv(os.path.join(data_dir, files_large["vector"]))
list_data_large = pd.read_csv(os.path.join(data_dir, files_large["list"]))
set_data_large = pd.read_csv(os.path.join(data_dir, files_large["set"]))

# Insert time plot
fig_insert = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_large, list_data_large, set_data_large]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_insert.add_trace(go.Scatter(
        x=grouped.index, y=grouped["insert_time_ms"],
        mode='lines+markers', name=label
    ))
fig_insert.update_layout(
    title="<b>Insert Times (LargeStruct)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_insert.show()
fig_insert.write_image(os.path.join(plot_dir, "insert_times_plot_large.png"))

# Remove time plot
fig_remove = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_large, list_data_large, set_data_large]):
    grouped = df.groupby("N").mean(numeric_only=True)
    fig_remove.add_trace(go.Scatter(
        x=grouped.index, y=grouped["remove_time_ms"],
        mode='lines+markers', name=label
    ))
fig_remove.update_layout(
    title="<b>Remove Times (LargeStruct)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_remove.show()
fig_remove.write_image(os.path.join(plot_dir, "remove_times_plot_large.png"))

# Insert + Remove time plot
fig_total = go.Figure()
for label, df in zip(["vector", "list", "set"], [vector_data_large, list_data_large, set_data_large]):
    grouped = df.groupby("N").mean(numeric_only=True)
    total_time = grouped["insert_time_ms"] + grouped["remove_time_ms"]
    fig_total.add_trace(go.Scatter(
        x=grouped.index, y=total_time,
        mode='lines+markers', name=label
    ))
fig_total.update_layout(
    title="<b>Total Times (Insert + Remove, LargeStruct)</b><br><i>Vector, List, and Set</i>",
    xaxis_title="Length of Container (N)",
    yaxis_title="Time (ms)",
    legend_title="Container",
    template="plotly_white"
)
fig_total.show()
fig_total.write_image(os.path.join(plot_dir, "total_times_plot_large.png"))

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

# LargeStruct data
pivot_large = make_pivot_table({
    "vector": vector_data_large,
    "list": list_data_large,
    "set": set_data_large
})
row_colors_large = get_row_colors(len(pivot_large))
fig_pivot_large = go.Figure(data=[go.Table(
    columnwidth=[60] + [120] * (len(pivot_large.columns) - 1),
    header=dict(
        values=[f"<b>{col}</b>" for col in pivot_large.columns],
        fill_color='#2a3f5f',
        font=dict(color='white', size=15, family='Arial Black'),
        align='center',
        line_color='white',
        height=36
    ),
    cells=dict(
        values=[pivot_large[col] for col in pivot_large.columns],
        fill=dict(color=[row_colors_large]),
        align='center',
        font=dict(color='black', size=14, family='Helvetica'),
        line_color='white',
        height=30,
    )
)])
fig_pivot_large.update_layout(
    title=dict(
        text="<b>Mean Insert & Remove Times (LargeStruct)</b><br><span style='font-size:14px;'>Lower is better</span>",
        x=0.5,
        xanchor="center",
        font=dict(size=20, family="Arial Black")
    ),
    margin=dict(l=20, r=20, t=80, b=20),
    width=1100,
    height=550,
    paper_bgcolor="#f8f9fc",
)
fig_pivot_large.write_image(os.path.join(plot_dir, "pivot_table_large.png"))