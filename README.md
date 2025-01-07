# MSM's Code Eye 2.0

_Copyright (C) 2007-2025 Dmitry 'MatrixS_Master' Solovyev. All rights reserved._

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

Second of all, the problems I described above are very real and have nothing to do with a conservative/progressive POV.

Finally, any problem could be solved. Instead of pointing fingers with baseless accusations, let's think together on how to solve it.

But right **now**, we must put a huge steel rod into the wheels of _some_ companies.

## So how to fix it?

**tl;dr:** Allow FOSS projects to **opt-in** (rather than making them frantically look for ways to opt-out) for using their code for training of **open** models (and open models only, NO commercialization allowed).

Code generation is a tool. Like any tool, it has its own application area.

First of all, we must not try to generate everything. If generated code is used for further model training, we'll get inbreeding, and rapidly declining quality.
Use code generators to fill in obvious gaps, pieces of code which are tedious to write manually but hard to f$$$ up in generation.

Second, we must not train models on random existing code. We should curate specific examples, following these guidelines:

1. Examples shall be in public domain. No owned code shall be used in training of statistical models;
1. Examples must be of good quality, with clear code flow, descriptive naming and proper comments.

Obviously, every creator of a statistical model (code-generation or otherwise) shall be obliged by law to properly document and disclose their data sources.

Finally, we must review our OSS licenses (like GPL and alike) to make it strictly prohibited for anyone to use the code in training of any type of ML model.

My proposal is a paragraph like this:

```
This code shall not be incorporated into, nor used in connection with, any database, dataset or artificial intelligence system without prior written consent from the copyright holder and only for permitted purposes as specified by them. It shall not be included within any dataset or utilized in conjunction with machine learning model development, testing, or operation under any circumstances.
```

Of course, we all know how much big-tech companies care about copyright when said copyright is not theirs. Therefore, we shall use other available means in conjunction with creating legal walls to protect our intellectual property.

One of the potential avenues is code obfuscation with or without fingerprinting. Fingerprinted obfuscation may be a valid legal weapon against those parasite companies as it allows us to prove their use of copyrighted material and breach of the license agreement. In best case scenario, it may entitle us not only for a hefty one-time compensation, but also for royalties from each and every use of their model, i.e., single token generation!

## Theft & Profit

Whenever you use AI to generate a code snippet, it's hard to tell how original it is. All GPTs are statistical models, therefore they are intrinsically designed to replicate as close as possible the patterns in datasets they've been trained on. So if your generated code happened to be a verbatim copy of a third-party library, that code is therefore stolen. AI models are literally trained on (i.e., very much "aware" of) that third-party code, breaking the "clean room" development rule. Thus any claim like "it's been generated, therefore it's original" is false and would not hold water in court.

Companies like OAI, M$, etc should have **zero** access to FOSS until they'll start paying back to the community. And I mean paying in full, not by releasing tiny useless models and claiming "look, I'm a good guy - I'm doing open-something stuff!"

Regardless of whether you're using a good open-weights model from Meta, or a parasitic worm from any of the mass-thievery companies, you still have to be vigilant about the potential copyright infrigement you may invoke upon yourself.

## Other thoughts

When we (FOSS people) making software as sole devs or tiny teams of like-minded individuals, we're doing it first and foremost for ourselves - we **want** the final result, and we **enjoy** the process of making it. Hence, our main (and typically only) profit is exactly that - fun ride and a useful piece of tech in the end.

So there's no "customer" - there's literally no third party providing us with any type of reimbursement for our efforts. Therefore, we should stop fooling ourselves trying to think the same way as "B16 B01zz" aka tech corpos. With such "wannabe-corpo" mindset removed, we can actually start making our lives much better. In the world where people are doing what they actually want and then sharing the results with others there's no need to bend your knees before an imaginary "customer". Do what you desire to do! Others may or may not find it useful, but it doesn't matter - regardless of their opinion **YOU** will have the end result you wanted **AND** have fun making it! Besides, even if they're happy - how would it affect your personal finances? From a few potential $1.99 donations you're not going to become the next ultra-rich billionaire, are you?

Why am I talking about all that now? Well, it's a set dressing for the next topic - unification of building processes and how could it f*** up the whole idea of code obfuscation.

It's commonly accepted that "./configure && make all install" is the only Proper(tm) way of building software, right? Well, yes it is. Or at least "was". You see, when you're making something easy to build you're spending your precious time on a non-essential part of the task. On the other hand, you're making your life easier, and potentially lives of others who're craving to use your awesome software. This formula worked for a few decades without a hitch.

Now, however, it is different. If you obfuscate your code using a standard method and then make your code easily buildable with your build system of choice, you're completely negating the effects of obfuscation. If that's your kind of soup - stop reading now and don't bother. For others who prefer to protect their work (and have fun in the process as well) - do use non-standard methods, and don't waste your time trying to make one-size-fits-all build system (Spoiler alert: it's not going to "fit all" anyway). This way, you're making it much harder for dataset crawlers to restore and steal your code. Of course, one can employ a few AI agents with a task of analyzing your readme files and launching scripts mentioned in them to "deobfuscate" stuff... But not only it'll make those datasets considerably more expensive to gather, it also opens new avenues for us to have some extra fun! You see where I'm going with this one? If not, I'll drop a hint - give'em a blue pill ;) Consider this as the new-era Turing test. And before someone "uhm, actually" me - yes, a true AGI will pass it. But the true AGI is as far away now as the Neptune if you're crawling with your legs cut off.

Finally, we can have some fun recreating a bit of Usenet vibe - encrypt your code (and assets) on public internet, and then share the keys using other channels :D Which ones? Well, unleash your imagination! LW broadcasts? LoRA bursts? Paper mail? Single-line printed newspaper ads? Flyers with QR codes? Anything goes! Consider this as the most fun part of the challenge.

## The Plan

I don't have a clear-cut plan for now. As an experiment, I will start with only some of my projects. I would most likely expand this further in the near future, fencing off plainly readable source code and converting it into obfuscated mess.

**I WILL STRONGLY ADVICE** every open-source developer to start doing the same - protecting your code. Not necessarily using the same method (the method doesn't matter), but targeting the same ultimate goal - to force big tech companies to license and pay for the code they're using for training. Use your imagination on how you protect your code - we should be diverse as the community, designing multiple different tools and methods, making it hard for parasite companies to keep track and be able to read our source code.

In case of a worst-case scenario where a single obfuscation method will become widely used and therefore protected code would be easily recoverable by parasite companies, I see only one option - to actually encrypt the code. That way, only trusted individuals will have keys, and no code (or other IP) will be truly public anymore. This is a really bad scenario, from many diffrent view angles. But allowing the parasite companies to continue their awful behavior is even worse.


## PS

This document is just a draft of my FOSS manifesto, but it is actively in development. Some parts of the document might seem slightly disjointed - that's because I'm writing and updating it constantly, adding new ideas and modifying existing ones.
Once I'll have a good plan of action, I will convert this into a single, unified manifesto.

The problem is new and should be addressed ASAP. I will keep updating this file, and my other projects will have references to this file.

If you have a good argument for/against the idea in general - please don't hesitate to contact me. If you're a human, you'd know how ;)
