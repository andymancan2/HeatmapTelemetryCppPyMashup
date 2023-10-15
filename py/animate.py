## @file animate.py
#Script to display heatmaps of telemetry data in shared memory.

# https://matplotlib.org/stable/gallery/images_contours_and_fields/image_annotated_heatmap.html
# 

##! @cond Doxygen_Suppress

import matplotlib.pyplot as plt
import matplotlib.widgets as widget

import numpy as np
import matplotlib
import matplotlib as mpl


import rwshm
from telemetry import *
from rwshm import *

## Common code for creating a heatmap
#https://matplotlib.org/stable/gallery/images_contours_and_fields/image_annotated_heatmap.html
def heatmap(data, row_labels, col_labels, ax=None,
            cbar_kw=None, cbarlabel="", **kwargs):
    """
    Create a heatmap from a numpy array and two lists of labels.

    Parameters
    ----------
    data
        A 2D numpy array of shape (M, N).
    row_labels
        A list or array of length M with the labels for the rows.
    col_labels
        A list or array of length N with the labels for the columns.
    ax
        A `matplotlib.axes.Axes` instance to which the heatmap is plotted.  If
        not provided, use current axes or create a new one.  Optional.
    cbar_kw
        A dictionary with arguments to `matplotlib.Figure.colorbar`.  Optional.
    cbarlabel
        The label for the colorbar.  Optional.
    **kwargs
        All other arguments are forwarded to `imshow`.
    """

    if ax is None:
        ax = plt.gca()

    if cbar_kw is None:
        cbar_kw = {}

    # Plot the heatmap
    im = ax.imshow(data, **kwargs)

    # Create colorbar
    cbar = ax.figure.colorbar(im, ax=ax, **cbar_kw)
    cbar.ax.set_ylabel(cbarlabel, rotation=-90, va="bottom", fontsize=16)
    cbar.ax.tick_params(labelsize=16)

    # Show all ticks and label them with the respective list entries.
    ax.set_xticks(np.arange(data.shape[1]), labels=col_labels)
    ax.set_yticks(np.arange(data.shape[0]), labels=row_labels)

    # Let the horizontal axes labeling appear on top.
    ax.tick_params(top=True, bottom=False,
                   labeltop=True, labelbottom=False)

    # Rotate the tick labels and set their alignment.
    #plt.setp(ax.get_xticklabels(), rotation=-30, ha="right", rotation_mode="anchor")
    plt.setp(ax.get_xticklabels(), rotation=0, ha="right", rotation_mode="anchor")

    # Turn spines off and create white grid.
    ax.spines[:].set_visible(False)

    ax.set_xticks(np.arange(data.shape[1]+1)-.5, minor=True)
    ax.set_yticks(np.arange(data.shape[0]+1)-.5, minor=True)
    ax.grid(which="minor", color="w", linestyle='-', linewidth=3)
    ax.tick_params(which="minor", bottom=False, left=False)

    return im, cbar

np.random.seed(19680801)
global treader

##! \{
fig, ax = plt.subplots(figsize=(16, 12)) ## Figure size
fig.subplots_adjust(bottom=0.2) ## Adjust the bottom.
##! \}
## Create the telemetry reader of shared memory.
treader = reader()

## Create X axis labels.
xlabels = [f"{i} T" for i in range(8)] 
## Create Y axis labels
ylabels = [f"{i} E" for i in range(8)] 

treader.clearTelemetry()
hm_im, hm_cbar = heatmap(treader.bitCounts, ## Create heatmap image and color bar legend.
                       xlabels, 
                       ylabels, 
                       ax = ax, 
                       cmap = "rainbow", ##The colormap
                       cbarlabel = "            Bit count") ## Color bar label.
ax.xaxis.label.set_size(24)     # change xlabel size
ax.yaxis.label.set_size(24)     # change ylabel size
ax.title.set_size(32)           # change subplot title size
fig.suptitle('Animate Telmetry', fontsize=32)
ax.set_xlabel('Entries per thread', fontsize=24)
ax.set_ylabel('Threads', fontsize=24)
plt.xticks(fontsize=16) ## Set the x axis font size.
plt.yticks(fontsize=16) ## Set the y axis font size.

print( "telemetry.kNumThreads = %d" % telemetry.kNumThreads)
print( "telemetry.kNumEntriesPerThread = %d" % telemetry.kNumEntriesPerThread)
print( "telemetry.kNumEntries = %d" % telemetry.kNumEntries)
plt.ion
plt.show
#sampleIdx = 0
ax.set_title(f"frame 0", fontsize=24)
fig.tight_layout()
# The for loop below is where the animation happens.
for i in range(telemetry.kMaxFrames):
   treader.gatherTelemetryBitCounts( i )
   hm_im.set_data( treader.bitCounts )
   hm_im.set_clim( 0, treader.bitCounts.max() )
   ax.set_title(f"frame {i}", fontsize=24)
   plt.pause(0.001)

fig.tight_layout()
plt.show()
del treader

//! @endcond
