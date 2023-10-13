<header>

<!--
  <<< Author notes: Heatmaps with cpp and python via shared memory. >>>
  Include a 1280×640 image, course title in sentence case, and a concise description in emphasis.
  In your repository settings: enable template repository, add your 1280×640 social image, auto delete head branches.
  Add your open source license, GitHub uses MIT license.
-->

# GitHub Page for displaying Heatmaps of telemetry data with cpp + python via shared memory.

10/15/23 This page is underconstruction.  Expect version 1.0 available in a few days.
This software is currently tested _

</header>

<!--
  <<< Author notes: Step 1 >>>
  Choose 3-5 steps for your course.
  The first step is always the hardest, so pick something easy!
  Link to docs.github.com for further explanations.
  Encourage users to open new tabs for steps!
-->
## Telemetry data
This is raw data that we want to visualize to better understand its meaning.
The word telemetry describes an embedded system or application is generating the data.
For example a buffer is shared between an FPGA device and a linux host.
A more specific example is a infrared camera that sampling pictures of your home furnaace.
* Samples are taken at a periodic rate and we want to animate to observer changes.
This project has a C++ program called "simSystemWithTelemetry" for an imaginary system of telemetry data.
* There are 8 threads with 8 entryies per thread, thus 64 32-bit entries per sample(frame).
* There are 64 samples(frames) taken.
* To generate a color we count the #'s of 1's(bits) in the 32-bit entry, thus color will increase over time.

## Heatmaps
An example heatmap of telemetry data for the 64th frame of "simSystemWithTelemetry".
![example heatmap](heatmap.jpg)

## Step 1: Enable GitHub Pages

_Welcome to GitHub Pages and Jekyll :tada:!_

The first step is to enable GitHub Pages on this [repository](https://docs.github.com/en/get-started/quickstart/github-glossary#repository). When you enable GitHub Pages on a repository, GitHub takes the content that's on the main branch and publishes a website based on its contents.

### :keyboard: Activity: Enable GitHub Pages

1. Open a new browser tab, and work on the steps in your second tab while you read the instructions in this tab.
1. Under your repository name, click **Settings**.
1. Click **Pages** in the **Code and automation** section.
1. Ensure "Deploy from a branch" is selected from the **Source** drop-down menu, and then select `main` from the **Branch** drop-down menu.
1. Click the **Save** button.
1. Wait about _one minute_ then refresh this page (the one you're following instructions from). [GitHub Actions](https://docs.github.com/en/actions) will automatically update to the next step.
   > Turning on GitHub Pages creates a deployment of your repository. GitHub Actions may take up to a minute to respond while waiting for the deployment. Future steps will be about 20 seconds; this step is slower.
   > **Note**: In the **Pages** of **Settings**, the **Visit site** button will appear at the top. Click the button to see your GitHub Pages site.

<footer>

<!--
  <<< Author notes: Footer >>>
  Add a link to get support, GitHub status page, code of conduct, license link.
-->

---

Get help: [Post in our discussion board](https://github.com/orgs/skills/discussions/categories/github-pages) &bull; [Review the GitHub status page](https://www.githubstatus.com/)

&copy; 2023 GitHub &bull; [Code of Conduct](https://www.contributor-covenant.org/version/2/1/code_of_conduct/code_of_conduct.md) &bull; [MIT License](https://gh.io/mit)

</footer>
