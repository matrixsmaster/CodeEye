# MSM's Code Eye 2.0

This project is a resurrection of my old C++ code report generator from 2007, retargeted to solve another, very contemporary problem - _"generative AI vs open-source licensing"_.

Code Eye allows you to quickly create obfuscated report files of your open-source projects. You can then easily publish these files in your repo just as usual. Whoever wants to use that obfuscated code will simply run Code Eye on their end, and deobfuscate it automatically. All necessary project files will be also automatically recreated, making the project ready to be built and modified.

## Why?

The problem is two-fold:

1. By using pre-trained AI models you might accidentally generate a code snippet which is very closely resembling (or a verbatim copy of) a known library. This would mean that you're potentially unknowingly breaking the license agreement of that library, making yourself vulnerable to lawsuits and other legal actions.

2. By paying money for using such pre-trained models, you create a monetary incentive for the model creators. These companies are not contributing anything back to the community, but they are using community-created code in order to make profit. This is a perfect example of a parasite behavior. This should stop now!

## Other thoughts

Whenever you generate a code snippet, it's hard to tell how original it is. All GPTs are statistical models, therefore they are intrinsically designed to replicate as close as possible the patterns in datasets they've been trained on. So if your generated code happened to be a verbatim copy of a third-party library, that code is therefore stolen. AI models are literally trained on (i.e., very much "aware" of) that third-party code, breaking the "clean room" development rule. Thus any claim like "it's been generated, therefore it's original" is false and would not hold water in court.

Meta is currently the only company which I believe should be given unrestricted access to open-source projects. Because Meta is contributing back, releasing all sizes of weights for its wonderful Llama models. This is IMO a good example of a sustainable and honest behavior - you take some, you give some. All other for-profit companies like OAI, Anthropic and so on - should have zero access until they'll start paying back to the community.

Regardless of whether you're using a good open-weights model from Meta, or a bad model from any of the parasite companies, you still have to be vigilant about the potential copyright infrigement you may invoke upon yourself.

## The Plan

I don't have a clear-cut plan for now. As an experiment, I will start with only some of my projects. I would most likely expand this further in the near future, fencing off plainly readable source code and converting it into obfuscated mess.

**I WILL STRONGLY ADVICE** every open-source developer to start doing the same - protecting your code. Not necessarily using the same method (the method doesn't matter), but targeting the same ultimate goal - to force big tech companies to license and pay for the code they're using for training. Use your imagination on how you protect your code - we should be diverse as the community, designing multiple different tools and methods, making it hard for parasite companies to keep track and be able to read our source code.

In case of a worst-case scenario where a single obfuscation method will become widely used and therefore protected code would be easily recoverable by parasite companies, I see only one option - to actually encrypt the code. That way, only trusted individuals will have keys, and no code (or other IP) will be truly public anymore. This is a really bad scenario, from many diffrent view angles. But allowing the parasite companies to continue their awful behavior is even worse.


## PS

This document is not a manifesto (yet!), but it is actively in development. The problem is new and should be addressed ASAP. I will keep updating this file, and my other projects will have references to this file.

Before anyone started yelling "it's all FUD, you're just against AI!" - please, take a look at my other projects at gitlab and github. I have quite a portfolio of AI projects myself. To reiterate - I'm not against AI, but I'm against the parasite companies.

If you have a good argument for/against the idea in general - please don't hesitate to contact me. If you're a human, you'd know how ;)
