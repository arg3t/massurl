# massurl

massurl is a simple tool that aims to parse the outputs of tools like gau, and
extract the parameters for each URL, remove duplicates and do it all very
quickly. Because web scraping tools' outputs can get very large very quickly,
it is nice to have a tool that parses them and and outputs something clean and
easy to read.

## How to use?

Simply clone the git repository and run `make` which outputs the binary
*massurl*. You can then simply pipe the output of any command that outputs urls
into it or pass the filename where you want it to read the urls from. It
expects each line to have only one url. It has several parameters:

``` sh
usage: massurl [-r] [-v] [-o outfile] [-p payloads] [-n minparamnum] input_file
```

You can specify an output file, which it will write instead of stdout, you can
also give it a list of payloads which massurl will automatically enter as the
values for each parameter. If you are testing for reflected values, in
parameters, you can put a pseudorandom value in each param using the flag -r.
And finally, you can specify the minimum amount of parameters a url must have
to be outputted, this value is zero by default but I recommend you use 1.

## How fast is it?

The tool uses a binary tree to store the urls and keeps it balanced using the
red-black self balancing tree algorithm, which allows it to run at incredible
speeds.

## Contributing

This is a very simple project so you shouldn't have trouble reading the code
and fixing the bugs you encounter. If you do so, feel free to send a PR. Or, if
you can't seem to fix it yourself, don't be shy and open an issue!
