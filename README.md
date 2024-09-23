# MSM's Code Eye 2.0

This project is a resurrection of my old C++ code report generator from 2007, retargeted to solve another, very contemporary problem - _"generative AI vs open-source licensing"_.

Code Eye allows you to quickly create obfuscated report files of your open-source projects. You can then easily publish these files in your repo just as usual. Whoever wants to use that obfuscated code will simply run Code Eye on their end, and deobfuscate it automatically. All necessary project files will be also automatically recreated, making the project ready to be built and modified.

## Why?

The _"generative AI vs open-source licensing"_ problem is two-fold:

1. By using pre-trained AI models you might accidentally generate a code snippet which is very closely resembling (or a verbatim copy of) a known library. This would mean that you're potentially unknowingly breaking the license agreement of that library, making yourself vulnerable to lawsuits and other legal actions.

2. By paying money for using such pre-trained models, you create a monetary incentive for the model creators. These companies are not contributing anything back to the community, but they are using community-created code in order to make profit. This is a perfect example of parasitic behavior. This has to stop _now_!

## How does CodeEye help?

Code Eye is just a simple tool. It's more of an experiment on how can we protect our code from automatic dataset scrapers, in attempt to avoid the two problems listed above.

In theory, if no model will be trained using open-source code, the problems listed above would automatically go away.

## This is wrong... Or is it?

_"But wait!"_, I hear you asking, _"how about code generation? I like generating my python code using copilot/codellama/etc!"_. My response to this: learn programming (and proper languages)!

Harsh? Perhaps. But there's a good reason for it - the more code we generate, the less quality and variety we'll get.
Works like inbreeding... literally.

Ultimately, if all code will be generated (and newer models trained on _that_), it'll look absolutely the same - inefficient, slow, buggy, unelegant mess. Almost like any JS code repo these days, but spread over to all other languages.
Horrified? Me too!

### It's not constructive!

I can easily see arguments in line with _"you're just against the change, and your view is too conservative, stale and wrong"_. Well, this is a false statement.

First of all, I'm developing my own AI tools. I've been doing that since 2003, way before most of the "you're an old man!" crowd even been born.
So evidently, I'm not against the change.

Second of all, the problems I described above are very real and have nothing to do with conservative POV.

Finally, any problem could be solved. Instead of pointing fingers with baseless accusations, let's think together on how to solve it.
But right **now**, we must put a huge steel rod into the wheels of _some_ companies.

## So how to fix it?

Code generation is a tool. Like any tool, it has its own application area.

First of all, we must not try to generate everything. If generated code is used for further model training, we'll get inbreeding, and rapidly declining quality.
Use code generators to fill in obvious gaps, pieces of code which are tedious to write manually.

Second, we must not train models on random existing code. We should curate specific examples, following these guidelines:

1. Examples shall be in public domain. No owned code shall be used in training of statistical models;
1. Examples must be of good quality, with clear code flow, descriptive naming and proper comments.

Obviously, every creator of a statistical model (code-generation or otherwise) shall be obliged by law to properly document and disclose their data sources.

## Other thoughts

Whenever you generate a code snippet, it's hard to tell how original it is. All GPTs are statistical models, therefore they are intrinsically designed to replicate as close as possible the patterns in datasets they've been trained on. So if your generated code happened to be a verbatim copy of a third-party library, that code is therefore stolen. AI models are literally trained on (i.e., very much "aware" of) that third-party code, breaking the "clean room" development rule. Thus any claim like "it's been generated, therefore it's original" is false and would not hold water in court.

Meta is currently the only company which I believe is doing the right thing. Because Meta is contributing back, releasing all sizes of weights for its wonderful Llama models. This is IMO a good example of a sustainable and honest behavior - you take some, you give some.

All other for-profit companies like OAI, Anthropic and so on - should have zero access until they'll start paying back to the community.

**However**, regardless of whether you're using a good open-weights model from Meta, or a bad model from any of the parasite companies, you still have to be vigilant about the potential copyright infrigement you may invoke upon yourself.

## The Plan

I don't have a clear-cut plan for now. As an experiment, I will start with only some of my projects. I would most likely expand this further in the near future, fencing off plainly readable source code and converting it into obfuscated mess.

**I WILL STRONGLY ADVICE** every open-source developer to start doing the same - protecting your code. Not necessarily using the same method (the method doesn't matter), but targeting the same ultimate goal - to force big tech companies to license and pay for the code they're using for training. Use your imagination on how you protect your code - we should be diverse as the community, designing multiple different tools and methods, making it hard for parasite companies to keep track and be able to read our source code.

In case of a worst-case scenario where a single obfuscation method will become widely used and therefore protected code would be easily recoverable by parasite companies, I see only one option - to actually encrypt the code. That way, only trusted individuals will have keys, and no code (or other IP) will be truly public anymore. This is a really bad scenario, from many diffrent view angles. But allowing the parasite companies to continue their awful behavior is even worse.


## PS

This document is not a manifesto (yet!), but it is actively in development. Some parts of the document might seem slightly disjointed - that's because I'm writing and updating it constantly, adding new ideas and modifying existing ones.
Once I'll have a good plan of action, I will convert this into a single, unified manifesto.

The problem is new and should be addressed ASAP. I will keep updating this file, and my other projects will have references to this file.

If you have a good argument for/against the idea in general - please don't hesitate to contact me. If you're a human, you'd know how ;)
