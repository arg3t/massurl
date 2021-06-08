# massurl
massurl is a simple tool that aims to parse the outputs of tools like gau, and extract the parameters for each URL, remove duplicates and do it all very quickly. Because web scraping tools' outputs can get very large very quickly, it is nice to have a tool that parses them and and outputs something clean and easy to read.

## How to use?
Simply clone the git repository and run `make` which outputs the binary *massurl*. You can then simply pipe the output of any command that outputs urls into it or use pass the filename where you want it to read the urls from. It expects each line to have only one url.

## Contributing
This is a very simple project so you shouldn't have trouble reading the code and fixing the bugs you encounter. If you do so, feel free to send a PR. Or, if you can't seem to fix it yourself, don't be shy and open an issue!
