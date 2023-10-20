## @file animate.py
#Script to display heatmaps of telemetry data in shared memory.

# https://matplotlib.org/stable/gallery/images_contours_and_fields/image_annotated_heatmap.html
# 


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

global gFig, gAx, gTeleReader
global gHeatmapImage, gHeatmapColorbar

## Initialize globals.
def initGlobals():
   """
   Initialize the globals for this script.
   """
   global gFig, gAx, gTeleReader
   fig, ax = plt.subplots(figsize=(16, 12)) ## Figure size
   ## Figure member.
   gFig = fig 
   ## Axis member.
   gAx   = ax 
   gFig.subplots_adjust(bottom=0.2) ## Adjust the bottom.
   ## Create the telemetry reader of shared memory.
   gTeleReader = reader()


## Open the heatmap graph.
def openGraph():
   """
   Open the heatmap graph.
   """
   global gFig, gAx, gTeleReader
   global gHeatmapImage, gHeatmapColorbar
   # Create X axis labels.
   xlabels = [f"{i} T" for i in range(8)] 
   # Create Y axis labels
   ylabels = [f"{i} E" for i in range(8)] 

   gTeleReader.clearTelemetry()
   hm_im, hm_cbar = heatmap(gTeleReader.bitCounts, ## Create heatmap image and color bar legend.
                       xlabels, 
                       ylabels, 
                       ax = gAx, 
                       cmap = "rainbow", ##The colormap
                       cbarlabel = "            Bit count") ## Color bar label.
   ## Heatmap image.
   gHeatmapImage = hm_im
   ## Heatmap color bar.
   gHeatmapColorbar = hm_cbar
   gAx.xaxis.label.set_size(24)     # change xlabel size
   gAx.yaxis.label.set_size(24)     # change ylabel size
   gAx.title.set_size(32)           # change subplot title size
   gFig.suptitle('Animate Telmetry', fontsize=32)
   gAx.set_xlabel('Entries per thread', fontsize=24)
   gAx.set_ylabel('Threads', fontsize=24)
   plt.xticks(fontsize=16) ## Set the x axis font size.
   plt.yticks(fontsize=16) ## Set the y axis font size.

## Animate the heatmap.
def animate():
   """
   Animate all frames of the telemetry data.
   """
   global gFig, gAx, gTeleReader
   global gHeatmapImage, gHeatmapColorbar
   print( "telemetry.kNumThreads = %d" % telemetry.kNumThreads)
   print( "telemetry.kNumEntriesPerThread = %d" % telemetry.kNumEntriesPerThread)
   print( "telemetry.kNumEntries = %d" % telemetry.kNumEntries)
   plt.ion
   plt.show
   gAx.set_title(f"frame 0", fontsize=24)
   gFig.tight_layout()
   # The for loop below is where the animation happens.
   for i in range(telemetry.kMaxFrames):
      gTeleReader.gatherTelemetryBitCounts( i )
      gHeatmapImage.set_data( gTeleReader.bitCounts )
      gHeatmapImage.set_clim( 0, gTeleReader.bitCounts.max() )
      gAx.set_title(f"frame {i}", fontsize=24)
      plt.pause(0.001)

   gFig.tight_layout()
   plt.show()

## main body of script.
def main():
   """
   Main body of script.
   """
   initGlobals()
   openGraph()
   animate()

main()


del gTeleReader
