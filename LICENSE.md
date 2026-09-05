# Block Engine License

**Version 5.1 — September 2026**

**Copyright © 2026 LeCatMan. All rights reserved.**

*This Version 5.1 supersedes and replaces Version 5.0 for all releases of Block Engine expressly distributed under Version 5.1. It does not retroactively replace Version 5.0 or any earlier version governing previously released copies.*

---

## 1. Definitions

For purposes of this License:

**"Block Engine"** means the software known as **Block Engine**, including its source code, compiled code, runtime, tools, libraries, editor, configuration files, build systems, project files, engine-provided assets, official documentation, official development files, and other materials identified by LeCatMan as part of the engine.

**"Engine Materials"** means materials included in Block Engine that are owned or controlled by LeCatMan, excluding Third-Party Materials.

**"Original Engine Materials"** means Engine Materials originally created or supplied by LeCatMan.

**"Third-Party Materials"** means materials included in, distributed with, or used by Block Engine that are not owned or controlled by LeCatMan and are subject to separate rights or licenses.

**"Block Engine API"** means the intentionally exposed programming, extension, integration, and interoperability interfaces of Block Engine through which independently created software may communicate with, control, extend, configure, automate, integrate with, inspect, or otherwise interact with Block Engine.

The Block Engine API includes, where intentionally exposed for development or interoperability purposes:

1. functions and methods;
2. classes, structures, records, unions, and data types;
3. enumerations and constants;
4. interfaces and contracts;
5. callbacks, events, hooks, and extension points;
6. commands and command interfaces;
7. scripting interfaces and bindings;
8. plugin interfaces;
9. module interfaces;
10. configuration interfaces;
11. inter-process and inter-module interfaces;
12. ABI or binary interfaces;
13. documented protocols;
14. documented file or data interfaces intentionally provided for interoperability;
15. public headers or interface declarations insofar as they expose the foregoing; and
16. official documentation describing or specifying the foregoing.

The Block Engine API does not include private implementation details merely because such details can be observed, inferred, reverse engineered, reconstructed, or used internally by Block Engine.

**API Designation.** LeCatMan may publish an official API designation document identifying which specific interface elements constitute part of the Block Engine API and which are private implementation. Absent an express designation of a specific interface element as private:

1. interface elements declared in any public header file are presumed part of the Block Engine API;
2. interface elements documented in any official Block Engine documentation are part of the Block Engine API; and
3. interface elements intentionally exposed through plugin or extension mechanisms are part of the Block Engine API.

Designations of elements as private apply prospectively only and do not affect API-Based Software that was commercially distributed or publicly released before the date of that designation.

**"API Interface Materials"** means the portions of Block Engine or its documentation that define or describe the Block Engine API, including declarations, signatures, type definitions, constants, interface definitions, callback definitions, protocol descriptions, and documentation reasonably necessary to use the Block Engine API.

**"API Client"** means independently created software that uses or communicates with the Block Engine API without itself constituting Block Engine, a Modified Engine, or Block Engine Development Technology.

**"API-Based Software"** means independently created software that uses or communicates with the Block Engine API, including plugins, add-ons, extensions, integrations, tools, utilities, services, Products, Mods, editors, automation software, and other software.

**"SDK"** means a software development kit or collection of development components intended to enable Developers to create, modify, build, test, debug, deploy, distribute, or otherwise develop software.

**"Modified Engine"** means Block Engine or Original Engine Materials that have been copied, modified, adapted, extended, translated, ported, reorganized, rewritten, combined, or otherwise changed in a manner that incorporates, reproduces, adapts, or is substantially derived from Block Engine or Original Engine Materials.

A Modified Engine includes a fork or derivative implementation containing or substantially based upon Original Engine Materials.

A work does not become a Modified Engine merely because it:

1. uses the Block Engine API;
2. interoperates with Block Engine;
3. implements compatible interfaces;
4. provides similar functionality;
5. uses similar ideas or concepts;
6. independently implements similar algorithms or techniques; or
7. is designed to replace or compete with Block Engine.

**"Substantially Derived"** means materially derived from, based upon, incorporating, reproducing, adapting, modifying, or materially relying upon Block Engine or Original Engine Materials.

Changing names, interfaces, programming languages, organization, implementation details, architecture, packaging, delivery methods, ownership, or branding does not by itself prevent material from being Substantially Derived.

However, similarity in ideas, concepts, functionality, algorithms, methods, interfaces, general design, interoperability, compatibility, or market purpose alone does not make independently created software Substantially Derived.

Independent implementation using generally available knowledge, techniques, standards, documentation, or technology does not by itself create a Modified Engine.

**Automated Transformation.** Substantially Derived includes material produced by automated, mechanical, or algorithmic transformation — including transpilation, code translation between programming languages, obfuscation, reformatting, variable renaming, structural reorganization, or automated refactoring — of Block Engine or Original Engine Materials, where the logical content, functional structure, or architecture of the resulting material remains materially derived from those original materials despite the transformation. The fact that such transformation was performed by a tool rather than a human being does not affect this determination.

Where transformation was performed for a legitimate, independently documentable technical purpose unrelated to circumventing this License, the degree of Substantial Derivation is evaluated by the degree of independent creative contribution present in the resulting material rather than by the mere fact of transformation. The burden of establishing a legitimate independent technical purpose rests on the person asserting it.

**"Development Technology"** means software or technology whose purpose or substantial functionality is to assist Developers in creating, modifying, building, testing, debugging, deploying, distributing, or otherwise developing software.

**"Block Engine Development Technology"** means Development Technology that contains, incorporates, reproduces, or is Substantially Derived from Block Engine, Original Engine Materials, or a Modified Engine.

Independently created software does not become Block Engine Development Technology merely because it:

1. works with Block Engine;
2. extends Block Engine;
3. uses the Block Engine API;
4. provides tools for Block Engine;
5. provides services for Block Engine users;
6. provides compatible functionality;
7. competes with Block Engine;
8. performs similar functions; or
9. is useful to Developers.

**"Substantial Functionality Test"** means the determination of whether Block Engine, a Modified Engine, or Block Engine Development Technology constitutes the substantial operational capability of an offering, evaluated by reference to all relevant objective factors, including:

1. whether, if Block Engine's functionality were removed, the remaining independently created material would constitute a viable, independently valuable commercial offering;
2. the proportion of the offering's operational capability derived from Block Engine or a Modified Engine versus independently created material;
3. whether the offering is marketed, described, or positioned to Developers principally in terms of Block Engine's capabilities; and
4. whether a Developer could perform the core engine development activities available in Block Engine — including scene management, rendering, asset pipeline, and build and deployment — through the offering without separately obtaining Block Engine.

Where factors (1) and (2) both indicate that Block Engine or a Modified Engine provides the substantial operational capability of an offering, that offering is presumed to constitute a Commercial Engine Offering without requiring proof of commercial value attribution or subjective intent. This presumption may be rebutted by clear and objective evidence of substantial independent functional capability. The analysis under the Substantial Functionality Test is based on the observable, objective characteristics of the offering rather than on stated intent or label.

**"Product"** means a game, application, interactive experience, simulation, end-user utility, entertainment software, total conversion, or other end-user software whose actual purpose and substantial functionality are directed toward providing functionality, content, or an experience to end users rather than providing Block Engine or a Modified Engine as Development Technology.

**"Mod"** means user-created content or software intended to modify, extend, replace, add to, or otherwise interact with a Product, including maps, levels, scripts, gameplay changes, total conversions, assets, plugins, extensions, tools, editors, utilities, and similar content.

**"Product Content"** means original code, artwork, audio, video, models, assets, documentation, data, and other material created by or for a Product or Mod creator, excluding Engine Materials and Third-Party Materials.

**"Engine Distribution"** means distributing Block Engine, a Modified Engine, or Block Engine Development Technology to another person or entity for the purpose of enabling or facilitating software development.

**"Remote Engine Service"** means providing access to Block Engine, a Modified Engine, or Block Engine Development Technology through a server, cloud system, browser, remote desktop, network, API, gateway, virtual machine, hosted environment, streaming system, build system, interactive service, or similar mechanism for software development.

**"Commercial Consideration"** means money, fees, subscriptions, licensing payments, contractual payments, mandatory purchases, paid access, required credits, required services, barter, or another economic benefit that is directly or materially provided in exchange for access to Block Engine, a Modified Engine, or Block Engine Development Technology.

A payment does not become Commercial Consideration merely because Block Engine is used somewhere in connection with a paid activity.

Revenue independently generated from a Product, Mod, service, website, advertisement, sponsorship, donation, community, consultancy, or other activity is not Commercial Consideration merely because Block Engine is used in connection with that activity.

However, a payment remains Commercial Consideration where the payment is actually required, directly or indirectly, to obtain Block Engine, a Modified Engine, or Block Engine Development Technology.

Infrastructure charges associated with a Remote Engine Service constitute Commercial Consideration where: (a) those charges exceed rates consistent with prevailing market prices for comparable standalone infrastructure services; or (b) the infrastructure services are not independently separable from engine access — that is, a Developer cannot obtain the infrastructure services without also receiving access to Block Engine, a Modified Engine, or Block Engine Development Technology. A charge is not excluded from Commercial Consideration merely because it is labeled as compute, storage, bandwidth, support, or maintenance.

**"Commercial Engine Offering"** means an Engine Distribution or Remote Engine Service through which Commercial Consideration is received in exchange for, or materially attributable to, providing Block Engine, a Modified Engine, or Block Engine Development Technology as Development Technology.

**"Distribute"** means to provide, publish, transfer, release, make available, supply, transmit, deliver, or otherwise provide software or copies of software to another person or entity, whether physically or electronically.

**"Developer"** means a person or entity using or seeking software for software development.

**"You"** means the individual or legal entity exercising rights under this License.

---

## 2. Ownership

LeCatMan retains all right, title, and interest in Block Engine and Original Engine Materials, including applicable copyright, trademark, and other intellectual property rights.

This License grants rights to use Block Engine. It does not transfer ownership of Block Engine or Original Engine Materials.

Original material independently created by You remains owned by You to the extent applicable law grants You ownership.

Third-Party Materials remain subject to their applicable licenses and rights.

Nothing in this License transfers ownership of independently created software to LeCatMan.

---

## 3. License Grant

Subject to this License, LeCatMan grants You a worldwide, non-exclusive, royalty-free license to:

1. use Block Engine;
2. inspect and study Block Engine;
3. modify Block Engine;
4. create Modified Engines;
5. create Products;
6. create Mods;
7. create plugins, add-ons, extensions, integrations, tools, utilities, services, and other software that works with Block Engine;
8. use the Block Engine API;
9. use API Interface Materials as reasonably necessary to develop API-Based Software;
10. create API Clients;
11. create API-Based Software;
12. integrate independently created software with Block Engine;
13. distribute Block Engine without charge;
14. distribute Modified Engines without charge;
15. distribute Products commercially or non-commercially;
16. distribute Mods commercially or non-commercially;
17. sell or license independently created Products, Mods, plugins, tools, services, and API-Based Software; and
18. create independently implemented software compatible with or competing with Block Engine.

Use of the Block Engine API does not require API-Based Software to be free of charge, open source, or licensed under this License.

Use of the Block Engine API does not by itself cause independently created software to become a Modified Engine or Block Engine Development Technology.

You may commercially use Block Engine to create Products, Mods, tools, services, client work, and other lawful works.

Except where expressly permitted by this License, these rights do not include the right to commercially offer Block Engine, a Modified Engine, or Block Engine Development Technology itself as Development Technology.

---

## 4. API Rights

The Block Engine API is intentionally provided as an extension, integration, automation, and interoperability boundary.

You may use the Block Engine API to:

1. create plugins;
2. create extensions;
3. create integrations;
4. create automation;
5. create editors and utilities;
6. communicate with the engine;
7. control engine systems;
8. add functionality;
9. replace functionality through exposed extension points;
10. provide alternative workflows;
11. connect external software;
12. create Products and Mods;
13. provide commercial services for Block Engine users; and
14. create independently developed software for Developers using Block Engine.

You may copy and include API Interface Materials to the extent reasonably necessary to build, compile, link, distribute, or operate API-Based Software.

This permission extends to API declarations, signatures, type definitions, constants, interface definitions, callback definitions, and similar interface material reasonably necessary for interoperability.

This permission does not authorize copying, distributing, or commercially providing Block Engine's private implementation, engine runtime, internal source code, or other Engine Materials except where another provision of this License expressly permits it.

An API Client may depend upon Block Engine.

An API-Based Software product may require the user to separately obtain Block Engine.

A fee charged for independently created API-Based Software, including a plugin, integration, automation system, tool, service, or other software, is permitted.

A fee charged for access to Block Engine itself, a Modified Engine itself, or Block Engine Development Technology itself as Development Technology is not permitted.

For avoidance of doubt:

> **Using the Block Engine API is permitted. Selling independently created software that uses the Block Engine API is permitted. Commercially providing the engine itself as Development Technology is not permitted.**

---

## 5. Commercial Products

You may use Block Engine and Modified Engines to create Products.

You may:

1. publish Products;
2. distribute Products;
3. license Products;
4. sell Products;
5. commercially exploit Products;
6. provide Products through digital distribution;
7. provide Products through physical distribution;
8. provide Products through subscription or paid access;
9. license Product Content under terms of Your choice; and
10. commercially provide services associated with Products.

A Product may contain Engine Materials and Modified Engine code, including substantial portions of such material, where incorporated into the Product as part of its operation and otherwise permitted by this License.

The commercial sale, licensing, operation, or distribution of a genuine Product does not by itself constitute a Commercial Engine Offering.

A Product may generate revenue through:

1. sales;
2. subscriptions;
3. advertising;
4. sponsorship;
5. donations;
6. in-app purchases;
7. paid services;
8. licensing;
9. crowdfunding; or
10. other lawful revenue models.

This permission does not apply where the Product is merely a wrapper, shell, launcher, demonstration, sample, template, nominal application, developer test environment, or other arrangement whose actual purpose or substantial functionality is to provide Block Engine, a Modified Engine, or Block Engine Development Technology to Developers.

---

## 6. Modding

Modding Block Engine Products is expressly permitted.

You may create, use, modify, publish, and distribute Mods, including:

1. maps and levels;
2. gameplay modifications;
3. scripts;
4. plugins;
5. extensions;
6. total conversions;
7. new game modes;
8. custom assets;
9. replacement assets;
10. tools;
11. editors;
12. utilities;
13. compatibility layers;
14. integrations; and
15. other independently created modifications or additions.

Mods may be distributed separately from the original Product.

You may commercially distribute or sell a Mod provided that the Mod itself is not a Commercial Engine Offering and does not separately provide Block Engine, a Modified Engine, or Block Engine Development Technology to Developers.

A Mod may contain Engine Materials or Modified Engine code where such inclusion is reasonably necessary for the Mod or Product to function and is otherwise permitted by this License.

Nothing in this Section requires Mods to be open source.

**Development Capability in Mods.** A Mod — including a total conversion — that provides end users with engine development tooling, build systems, general-purpose asset pipelines, or development interfaces enabling Developers to create further Products or Mods without separately obtaining Block Engine constitutes Block Engine Development Technology for the purposes of Section 7, regardless of its label as a Mod, total conversion, or expansion. The test is whether the Mod, in addition to providing end-user content, provides development capability that substitutes for obtaining Block Engine independently.

A Mod does not satisfy the requirement of separate independent acquisition of Block Engine merely because the Mod's users possess a copy of the host Product. The requirement is satisfied only where the Mod's users have independently obtained Block Engine under a license that permits the development activity in question, not merely a copy sufficient to play the host Product.

End-user modding tools included in a Mod or Product are evaluated by whether their scope and capability is proportionate to the modding activity the Product actually supports. A modding tool that exposes general-purpose engine development capabilities beyond what is needed to create content for that specific Product is not a genuine end-user modding tool for the purposes of this License.

---

## 7. Commercial Engine Offerings

You may not commercially offer Block Engine, a Modified Engine, or Block Engine Development Technology as Development Technology.

Without limiting this restriction, You may not:

1. sell Block Engine as an engine or development platform;
2. sell a Modified Engine as an engine or development platform;
3. rent or lease Block Engine or a Modified Engine;
4. charge a license fee for Block Engine, a Modified Engine, or Block Engine Development Technology;
5. require Commercial Consideration as a condition of obtaining Block Engine or its development functionality;
6. commercially distribute Block Engine, a Modified Engine, or Block Engine Development Technology as Development Technology;
7. commercially offer Block Engine as an engine, framework, SDK, development kit, editor, toolkit, library, middleware package, development platform, or substantially similar Development Technology;
8. commercially provide Block Engine through a cloud, server, browser, remote desktop, hosted environment, virtual machine, streaming system, build system, or similar remote system for software development;
9. operate a paid service whose purpose or substantial functionality is to provide Developers with Block Engine, a Modified Engine, or Block Engine Development Technology;
10. package, expose, proxy, mirror, wrap, embed, or otherwise commercially provide the substantial functionality of Block Engine or a Modified Engine as Development Technology;
11. commercially provide Block Engine or a Modified Engine through an API, gateway, wrapper, SDK, service, plugin, extension, or library where the underlying purpose is to provide the engine itself as Development Technology;
12. divide Block Engine across multiple commercial packages, services, repositories, accounts, components, entities, or transactions for the purpose of avoiding this Section;
13. make access to Block Engine conditional upon purchasing an unrelated Product or service where the purchase functions as consideration for obtaining the engine or its development functionality;
14. commercially provide a service whose substantial purpose is to give Developers development capabilities materially supplied by Block Engine or a Modified Engine;
15. commercially sublicense, resell, or redistribute Block Engine or a Modified Engine as a development product;
16. commercially bundle Block Engine or a Modified Engine with another development platform where the transaction materially charges for access to the engine or its development functionality;
17. commercially provide a paid installer, launcher, downloader, repository, mirror, or similar distribution mechanism where payment is required to obtain Block Engine or its development functionality;
18. require payment, paid membership, paid account status, paid credits, or another economic condition in order to obtain functionality that would otherwise constitute Block Engine or Block Engine Development Technology;
19. use contractors, affiliates, subsidiaries, resellers, partners, intermediaries, or related entities for the primary purpose of avoiding this Section;
20. otherwise structure an arrangement whose actual purpose or substantial effect is to commercially provide Block Engine, a Modified Engine, or Block Engine Development Technology to Developers;
21. commercially provide software where Block Engine's development functionality constitutes the substantial operational capability of the offering, as evaluated under the Substantial Functionality Test, regardless of the presence of additional independently created features, services, or interface layers. The addition of independently created features does not transform a commercial offering whose substantial operational value is derived from Block Engine into permitted API-Based Software; or
22. commercially provide a collection, bundle, or integrated suite of tools, components, libraries, integrations, plugins, or other software that, taken together as evaluated under the Substantial Functionality Test, substantially reproduces the development functionality of Block Engine — even where each individual component is claimed to be independently created API-Based Software — where the commercial value and primary purpose of the collection is to provide Developers with development capability materially equivalent to Block Engine. A collection substantially reproduces Block Engine's development functionality where a Developer using the collection can perform the core engine development activities available in Block Engine without separately obtaining Block Engine. Collections providing only specialized or narrow subsets of development functionality not equivalent to the engine as a whole are not presumed to substantially reproduce the engine.

**Proportional Functionality Presumption.** Where more than seventy percent (70%) of the development functionality available through a commercial offering is derived from Block Engine or a Modified Engine without material independent transformation — as measured by the range and depth of engine operations available to Developers through the offering — that offering is presumed to constitute a Commercial Engine Offering. This presumption may be rebutted by clear and convincing evidence of substantial independent functional value.

A service, plugin, extension, tool, API Client, or other software does not violate this Section merely because it is:

1. commercial;
2. paid;
3. useful to Developers;
4. specifically designed for Block Engine;
5. dependent on Block Engine;
6. connected to Block Engine;
7. capable of controlling Block Engine;
8. capable of extending Block Engine;
9. capable of automating Block Engine; or
10. commercially successful.

The restriction in this Section applies to commercial provision of **the engine or its development technology**, not commercial software that merely uses, integrates with, extends, or communicates with the engine.

---

## 8. Product Boundary

The permission to commercially distribute Products and Mods does not permit commercial provision of Block Engine, Modified Engines, or Block Engine Development Technology to Developers.

A Product or Mod does not become an Engine Distribution merely because it:

1. contains Engine Materials;
2. contains substantial Modified Engine code;
3. extensively uses Block Engine;
4. is proprietary;
5. is sold commercially;
6. earns revenue;
7. is distributed with a Product;
8. requires Engine Materials to operate; or
9. communicates extensively with Block Engine.

However, software whose actual purpose or substantial functionality — evaluated under the Substantial Functionality Test — is to provide Developers with Block Engine, a Modified Engine, or Block Engine Development Technology remains subject to Section 7 regardless of its label.

**Development Tooling Exclusion.** A genuine Product does not include engine development tooling — editors, build systems, compiler integrations, project management interfaces, asset pipelines directed at developers, or debugging environments — beyond what is reasonably necessary for end users to install, operate, play, or use the Product as an end user. The inclusion of engine development functionality directed at Developers rather than at end users is strong evidence that the distribution's actual purpose is to provide Development Technology.

A level editor or modding tool accessible to end users for the purpose of creating content for that specific Product does not by itself constitute engine development tooling for the purposes of this Section. However, a general-purpose engine editor, full asset pipeline, build system, or development environment whose scope exceeds what is needed to create content for that specific Product does. End-user modding and development tools within a Product are evaluated by whether their scope and capability is proportionate to the specific modding activity the Product actually supports.

A person may not avoid Section 7 by:

1. placing a nominal game around the engine;
2. adding minimal or unrelated content;
3. embedding the engine inside another application;
4. renaming the application;
5. changing the user interface;
6. separating the engine into multiple components;
7. providing the engine through multiple services or entities;
8. putting the engine behind an API;
9. wrapping the engine in independently created software;
10. distributing only selected engine components that collectively reproduce the engine's development functionality;
11. requiring a separate download that supplies the remaining engine functionality;
12. describing the arrangement as a plugin, extension, library, tool, service, or integration; or
13. selling an otherwise nominal Product whose substantial purpose is to provide development access to the engine.

The substance of the arrangement, evaluated under the Substantial Functionality Test, controls rather than its label.

A genuine Product remains permitted even where it contains or depends upon substantial Engine Materials, provided that the substantial purpose of the Product is to provide an end-user experience rather than to provide development technology to Developers.

---

## 9. Circumvention

You may not knowingly structure, divide, disguise, delegate, outsource, proxy, wrap, sublicense, or otherwise arrange an activity for the primary purpose of avoiding a restriction in this License.

This includes arrangements where multiple persons, entities, services, downloads, accounts, components, APIs, packages, or transactions collectively provide Block Engine, a Modified Engine, or Block Engine Development Technology as a Commercial Engine Offering.

A party may not rely on the fact that no single component is individually identical to Block Engine where the components are intentionally combined to provide substantially the same engine or development technology.

A party may not separate ownership, licensing, billing, hosting, distribution, or operation among different persons or entities for the primary purpose of avoiding a restriction that would apply if the arrangement were treated as a whole.

**Multi-Entity Arrangements.** An arrangement involving multiple persons or entities is evaluated as a whole rather than component-by-component. In evaluating whether a multi-entity or multi-component arrangement constitutes circumvention, the following are relevant factors:

1. whether the separate entities share common ownership, control, beneficial interest, or coordinated operation;
2. whether the transaction structure departs materially from how comparable legitimate independent businesses operate;
3. whether the arrangement produces a result that a single entity performing the same activity would be prohibited from producing under this License; and
4. whether the separation between entities or components provides any independent commercial rationale beyond the avoidance of this License.

No single factor is determinative, and the analysis is based on the substance and structure of the arrangement as a whole.

**Safe Harbor for Legitimate Separate Businesses.** An arrangement involving genuinely separate businesses — with independent ownership, independent commercial rationale, arms-length commercial terms, and independently valuable activities beyond engine provision — is not circumvention merely because the combined effect of those businesses results in Block Engine being available to Developers. The circumvention prohibition is directed at arrangements whose structure exists primarily to produce that combined result rather than for independent business reasons. The existence of commercial payment does not by itself establish circumvention. The relevant question is whether the arrangement is substantially providing Block Engine, a Modified Engine, or Block Engine Development Technology itself, evaluated under the Substantial Functionality Test.

This Section does not prohibit:

1. legitimate independent businesses;
2. Products;
3. Mods;
4. plugins;
5. APIs;
6. tools;
7. services;
8. integrations;
9. compatible software;
10. competing software; or
11. independently created implementations

merely because they interact with, extend, automate, replace, or compete with Block Engine.

---

## 10. Free Distribution

You may Distribute Block Engine or a Modified Engine without charge.

A free distribution must:

1. include this License;
2. retain applicable copyright and license notices;
3. identify material modifications where reasonably practical; and
4. not require Commercial Consideration as a condition of obtaining the engine.

A distributor may operate a website, repository, community, mirror, or other distribution service around a free distribution and may receive independent advertising, sponsorship, or donation revenue.

A donation is considered non-mandatory where a person may obtain the same Block Engine or Modified Engine distribution, with equivalent development functionality, without making the donation.

A free distribution may be accompanied by optional:

1. support;
2. consulting;
3. hosting;
4. training;
5. documentation;
6. services;
7. Products; or
8. other independently valuable offerings.

A free distribution may not be made nominally free while a mandatory payment, required purchase, required subscription, required account tier, paid membership, required service, or equivalent economic condition is actually necessary to obtain the engine or its development functionality.

**Functional Accessibility Requirement.** The free distribution path must be reasonably functional and accessible. A distribution path is not reasonably accessible where it imposes artificial technical barriers — including intentionally degraded download speeds, extended queuing, mandatory waiting periods disproportionate to server load, CAPTCHA abuse, or other friction — that are not present in the paid or donation-accelerated path and that are not the result of genuine, documented infrastructure limitations applying equally to the distributor's other services.

Where the free and paid download paths are served from the same infrastructure, materially different performance between paths is presumed to be artificial. Where served from different infrastructure, the distributor bears the burden of demonstrating that the difference in performance reflects genuine infrastructure capacity rather than deliberate design.

A distributor may accept payment for independently provided goods or services associated with a free distribution, provided that payment is not actually required as consideration for obtaining Block Engine or its development functionality.

---

## 11. Modified Engines

You may modify Block Engine for lawful purposes.

You may create forks, ports, adaptations, reorganizations, and other Modified Engines.

You may share Modified Engines without charge.

You retain ownership of original material independently created by You and incorporated into a Modified Engine, to the extent applicable law grants You ownership.

Those rights do not transfer ownership of Block Engine or Original Engine Materials.

A Modified Engine remains subject to this License.

A Modified Engine may not be commercially sold or commercially offered as Development Technology.

A Modified Engine may not be represented as the original, unmodified Block Engine.

A Modified Engine may be renamed, rebranded, reorganized, or substantially changed, but such changes do not remove the Modified Engine from the scope of this License where the resulting work remains Substantially Derived from Block Engine or Original Engine Materials.

You may not sublicense a Modified Engine in a manner that purports to remove the restrictions of this License from Block Engine or Original Engine Materials.

You may impose additional terms on Your own original material, provided those terms do not contradict or remove the rights and restrictions applicable to Block Engine and Original Engine Materials.

---

## 12. Internal Use

You may copy, modify, build, deploy, and provide Block Engine or Modified Engines to Your employees, contractors, agents, and internal systems where reasonably necessary for Your own internal development activities.

**Contractor Scope.** Internal use permits You to provide Block Engine access to contractors performing work under Your direction for Your projects. A contractor qualifies as internal for the purposes of this Section only where:

1. the work performed by the contractor is directed by You and serves Your projects;
2. the contractor does not receive engine access for use on projects not directed by You; and
3. the contractor's compensation does not include a component that functions as consideration for engine access independent of labor performed for Your directed projects.

Providing engine access to a person whose primary benefit from the arrangement is development access to Block Engine rather than compensation for services rendered to You constitutes an Engine Distribution, not internal use, regardless of how the relationship is labeled.

**Incidental Tool Safe Harbor.** A contractor may use Block Engine to create tools, utilities, or integrations reasonably incidental to performing their engagement for You, without that use constituting a separate Engine Distribution, provided those tools are not independently distributed to or made available to other Developers outside of that engagement.

Internal use does not constitute a Commercial Engine Offering merely because You:

1. operate a commercial business;
2. earn revenue;
3. charge clients;
4. create Products for sale;
5. create services for sale; or
6. perform development work for third parties.

You may use Block Engine internally to create:

1. Products;
2. Mods;
3. plugins;
4. tools;
5. services;
6. client work;
7. commercial software; and
8. other lawful works.

You may use Block Engine internally to perform development work for clients.

You may not use this Section as a disguised means of giving a client or other independent Developer commercial access to Block Engine, a Modified Engine, or Block Engine Development Technology as a development platform.

Providing a client with the finished work created using Block Engine is permitted.

Providing a client with Block Engine itself or development access to the engine is governed by the other provisions of this License.

---

## 13. Products Containing Engine Materials

You may include Engine Materials and Modified Engine code in a Product or Mod where permitted by this License.

You may commercially distribute and sell that Product or Mod.

The presence of Engine Materials inside a Product or Mod does not transfer ownership of those materials to You.

The permission to distribute Engine Materials as part of a Product or Mod exists solely to permit lawful distribution and use of that Product or Mod.

It does not permit the separate commercial provision of Block Engine, Modified Engines, or Block Engine Development Technology.

A recipient may receive Engine Materials as part of a Product or Mod to the extent reasonably necessary to install, execute, use, modify, or operate that Product or Mod.

A Product distributor is not required to make Product Content open source merely because Engine Materials are included in the Product.

Distribution of Engine Materials as part of a Product does not grant the recipient a separate right to commercially provide those Engine Materials as Development Technology.

---

## 14. Extraction and Redistribution

Engine Materials included in a Product or Mod remain subject to their applicable ownership and license terms.

To the extent permitted by applicable law, a recipient may not use Engine Materials obtained from a Product or Mod to:

1. sell the Engine Materials separately;
2. commercially distribute the Engine Materials separately;
3. create a commercial engine substantially based on Original Engine Materials;
4. create commercial Block Engine Development Technology from Original Engine Materials;
5. commercially provide Original Engine Materials to Developers as Development Technology; or
6. create a Commercial Engine Offering from Original Engine Materials.

Nothing in this Section restricts rights that applicable law or an applicable Third-Party Material license does not permit LeCatMan to restrict.

Nothing in this Section prohibits ordinary use, debugging, modification, reverse engineering, interoperability, or other activity otherwise permitted by this License or applicable law.

Third-Party Materials remain subject to their applicable licenses.

---

## 15. Services and Work Performed Using Block Engine

Nothing in this License prohibits You from earning money by using Block Engine.

You may provide paid:

1. game development;
2. software development;
3. programming;
4. consulting;
5. contracting;
6. education;
7. training;
8. support;
9. debugging;
10. customization;
11. integration;
12. maintenance;
13. porting;
14. asset creation;
15. hosting of Products;
16. operation of Products;
17. technical services; and
18. other services.

You may charge a client for work performed using Block Engine.

You may use Block Engine internally while performing paid services.

The thing being sold must be Your work, service, Product, Mod, plugin, tool, asset, or other independently provided value rather than commercial access to Block Engine, a Modified Engine, or Block Engine Development Technology itself.

A service that uses Block Engine internally to perform work for a client is permitted.

A service is not transformed into a Commercial Engine Offering merely because Block Engine is used behind the scenes.

This Section does not authorize commercial provision of Block Engine itself as Development Technology.

---

## 16. Plugins, Add-ons, Extensions, API-Based Software, and Independent Tools

Independently created plugins, add-ons, extensions, tools, libraries, editors, importers, exporters, integrations, utilities, middleware, assets, API Clients, API-Based Software, and other software designed to work with Block Engine are permitted.

Such software may be distributed commercially, including for payment, provided that the software:

1. is independently created;
2. does not contain or distribute Block Engine or a Modified Engine except as separately permitted by this License;
3. does not reproduce substantial portions of Original Engine Materials except as separately permitted by this License;
4. does not itself provide Block Engine or a Modified Engine as Development Technology;
5. does not merely repackage, proxy, mirror, wrap, or disguise Block Engine as independent software; and
6. does not otherwise constitute a Commercial Engine Offering.

Such software may:

1. use the Block Engine API;
2. depend upon Block Engine;
3. communicate with Block Engine;
4. extend Block Engine functionality;
5. modify or influence Block Engine through documented or intentionally exposed interfaces;
6. automate Block Engine;
7. provide new functionality to Developers;
8. provide commercial services to users of Block Engine;
9. integrate Block Engine with other software;
10. provide alternative interfaces or workflows for Block Engine;
11. provide independently created development tools for Block Engine;
12. be distributed through commercial marketplaces; and
13. be commercially licensed or sold.

**Collective Functionality.** A collection, bundle, or suite of API-Based Software products is not rendered independently permissible under this Section merely because each individual component is claimed to be independently created, where the collection is intentionally designed, marketed, or bundled to collectively reproduce Block Engine's development functionality as evaluated under the Substantial Functionality Test. Where such a collection is commercially offered and its primary commercial value to Developers is the engine development capability it collectively provides, that collection constitutes a Commercial Engine Offering subject to Section 7.

Use of the Block Engine API does not transfer ownership of the API, Block Engine, or Original Engine Materials to You.

Use of the Block Engine API does not require Your software to be open source or licensed under this License.

Software does not become Block Engine Development Technology merely because it is specifically designed for Developers using Block Engine or because it provides substantial additional functionality around Block Engine.

An independent tool remains independent where it communicates with Block Engine rather than incorporating or redistributing the engine implementation, except to the extent this License expressly permits such incorporation or redistribution.

---

## 17. Independent Competing Software

Nothing in this License prevents You or any other person from independently creating, publishing, distributing, licensing, selling, or operating software that:

1. competes with Block Engine;
2. replaces Block Engine;
3. implements similar features;
4. implements similar APIs;
5. implements compatible interfaces;
6. targets similar users;
7. targets the same market;
8. provides similar development workflows;
9. uses similar general architecture; or
10. performs substantially similar functions.

Independently created competing software is not subject to this License merely because it is functionally similar to Block Engine.

Nothing in this License grants LeCatMan ownership of independently created competing software.

Independent software becomes subject to this License only to the extent that it incorporates, reproduces, adapts, or is Substantially Derived from Block Engine or Original Engine Materials, subject to applicable law.

**Clean Room Safe Harbor.** An implementation developed through a documented clean-room process in which the persons responsible for implementation did not have access to, and did not reference, the source code of Block Engine or Original Engine Materials — relying only on publicly available documentation, the Block Engine API specification, and independently observable behavior — is not Substantially Derived from Block Engine solely because it implements compatible interfaces, functionality, or behavior. The person asserting the clean-room safe harbor bears the burden of establishing the process by reasonable documentary evidence.

---

## 18. Attribution and Branding

You may identify Your own modifications and original contributions as Your work.

You may not falsely represent:

1. Block Engine as having been created by You;
2. Original Engine Materials as having been created by You; or
3. a Modified Engine as the original, unmodified Block Engine.

You must retain applicable Block Engine copyright and license notices when distributing Block Engine or a Modified Engine.

**Affirmative Disclosure for Modified Engines.** When distributing a Modified Engine, You must include a reasonably prominent notice identifying that the distribution is based upon or derived from Block Engine. The notice must be:

1. visible to a recipient of the distribution before or at the time they receive the distribution;
2. included in primary documentation, release notes, or the distribution's main readme or equivalent;
3. sufficient to allow a recipient to locate this License; and
4. not buried in supplementary materials not ordinarily reviewed before relying on the software.

A notice substantially in the following form satisfies this requirement:

> *This software is based on Block Engine by LeCatMan and is distributed under the Block Engine License.*

A notice is not reasonably prominent where it appears only in a file not ordinarily presented to recipients, in metadata not visible during normal evaluation of the distribution, or in documentation not ordinarily reviewed before or during use of the software. The standard is whether a typical intended recipient would be made aware of the derivation before relying on the distribution.

Omission of required attribution is a material violation of this License.

You may state:

> Made with Block Engine.

Use of the Block Engine name, logo, or other marks does not grant trademark rights or imply endorsement, sponsorship, certification, partnership, or affiliation with LeCatMan.

You may truthfully state compatibility with Block Engine.

You may not use Block Engine branding in a manner reasonably likely to imply that Your software is officially published, certified, endorsed, or maintained by LeCatMan unless You have separate written permission.

---

## 19. Contributions

If You voluntarily contribute original code or other material to Block Engine or an official Block Engine repository, You retain ownership of that contribution unless You separately agree otherwise in writing.

By submitting a contribution for inclusion in Block Engine, You grant LeCatMan a worldwide, royalty-free, non-exclusive license to use, reproduce, modify, distribute, sublicense, and include that contribution in Block Engine and Modified Engines under this License.

This contribution license is limited to the rights reasonably necessary to develop, distribute, maintain, modify, and license Block Engine and Modified Engines.

Nothing in this Section transfers ownership of Your original contribution to LeCatMan.

**Contributor Patent Grant.** By submitting a contribution for inclusion in Block Engine, You additionally grant LeCatMan and all users of Block Engine a worldwide, royalty-free, non-exclusive, perpetual license under any patent claims owned or controlled by You that are necessarily infringed by the contribution, or by the combination of the contribution with Block Engine as it existed at the time of submission, to make, use, sell, offer for sale, import, modify, distribute, and otherwise exploit the contribution as part of Block Engine or any Modified Engine. This grant includes patent claims that would be necessarily infringed by a user exercising the rights granted by this License with respect to the contribution as incorporated into Block Engine.

**Contributor Representations.** By submitting a contribution, You represent, to the best of Your knowledge, that:

1. You are the sole author and owner of the contribution, or You have received express written authorization from all parties with ownership or employment rights in the contribution to submit it under the terms of this Section;
2. where the contribution was created as part of Your employment or in the scope of a contract that may vest ownership in another party, You have obtained that party's written authorization before submission;
3. You are not aware of any patent claims owned or controlled by You or Your employer that would be infringed by the contribution or its use within Block Engine and that You have not disclosed under the Contributor Patent Grant above; and
4. You have sufficient rights to submit the material under these terms.

Where a contribution arises from employment or a work-for-hire arrangement and the contributor provides an employer authorization form or equivalent written documentation, LeCatMan may rely on that documentation without independent verification.

If You become aware of any patent claim owned or controlled by You or Your employer that may be infringed by a previously submitted contribution after the time of submission, You agree to promptly disclose it to LeCatMan in writing.

You should not submit material that is subject to a license or contractual restriction incompatible with this Section unless that restriction is expressly disclosed and accepted by LeCatMan.

Third-Party Materials and material not legally controlled by You remain subject to their applicable rights.

---

## 20. Third-Party Materials

Block Engine may contain or depend upon Third-Party Materials.

Third-Party Materials remain subject to their applicable licenses.

Nothing in this License overrides, replaces, or restricts rights granted by an applicable Third-Party Material license.

LeCatMan does not grant rights in Third-Party Materials that LeCatMan does not legally possess.

You are responsible for complying with applicable Third-Party Material licenses.

Where practical, Block Engine distributions should identify applicable Third-Party Materials and their licenses.

Where a Third-Party Material license grants broader rights than this License, those broader rights remain available with respect to that Third-Party Material.

Where a Third-Party Material license imposes additional obligations, those obligations continue to apply.

The selection, compilation, configuration, and integration of Third-Party Materials into Block Engine constitutes Engine Materials to the extent of LeCatMan's original creative contribution in making those selections and integrations, even where the underlying Third-Party Materials remain separately licensed.

---

## 21. Source Code and Interface Material

Where Block Engine is distributed in source form, that source remains Engine Materials unless otherwise identified.

You may inspect, study, modify, build, and use the source code in accordance with this License.

You may distribute Modified Engines without charge as permitted by this License.

You must retain applicable copyright and license notices when distributing Block Engine or a Modified Engine.

API Interface Materials may be copied and distributed as reasonably necessary for API-based interoperability.

The permission to distribute API Interface Materials does not grant permission to distribute the Block Engine implementation merely because that implementation is reachable through or required by the interface.

Where an API header or similar file contains both:

1. API declarations reasonably necessary for interoperability; and
2. implementation material not reasonably necessary for interoperability,

the permission in this Section applies to the interface material to the extent reasonably necessary and does not independently authorize commercial distribution of the implementation material.

---

## 22. Remote and Hosted Use

You may use Block Engine on Your own hardware, servers, virtual machines, build systems, continuous-integration systems, or other infrastructure.

You may use Block Engine to build Products or perform paid services.

You may provide a Product or service to end users where Block Engine is used internally and the service does not expose Block Engine itself as Development Technology.

You may not commercially provide Developers with interactive or remote access to Block Engine, a Modified Engine, or Block Engine Development Technology where the purpose or substantial functionality is to enable those Developers to use the engine as a development platform.

A Product hosted on a server does not become a Commercial Engine Offering merely because Block Engine runs on that server.

**Infrastructure Charges.** Infrastructure charges associated with a Remote Engine Service constitute Commercial Consideration and render the service a Commercial Engine Offering where: (a) those charges exceed rates consistent with prevailing market prices for comparable standalone infrastructure services; or (b) the infrastructure services are not independently separable from engine access — that is, a Developer cannot obtain the infrastructure services without also receiving Block Engine, a Modified Engine, or Block Engine Development Technology.

Infrastructure charges at rates publicly consistent with comparable third-party cloud or infrastructure services — where a Developer could obtain equivalent standalone infrastructure at similar rates from the market — do not constitute Commercial Consideration for the engine solely because the engine runs on that infrastructure, provided the infrastructure is independently separable from engine access.

A paid development environment that provides Developers with Block Engine itself does constitute a Commercial Engine Offering even where:

1. the engine runs remotely;
2. the engine is hidden behind an interface;
3. the developer never receives a local copy;
4. the interface is an API;
5. access is provided through a browser;
6. access is provided through a virtual machine;
7. access is provided through a streaming system; or
8. the engine is bundled with unrelated services.

---

## 23. No Requirement to Open Source Product Content

Nothing in this License requires You to release Product Content, Mod Content, API-Based Software, or independently created software as source code solely because You use Block Engine.

You may keep Your independently created material proprietary.

You may license Your original work under terms of Your choice, provided that Your terms do not purport to remove rights in Block Engine, Original Engine Materials, or Third-Party Materials that You do not own.

This Section does not restrict obligations imposed by an applicable Third-Party Material license.

---

## 24. No Sublicensing of Engine Rights

The rights granted by this License are personal to You except to the extent this License expressly permits distribution of Block Engine, Modified Engines, Products, Mods, or other works.

You may not grant another person or entity a separate license to Block Engine or Original Engine Materials that purports to:

1. remove or weaken the restrictions of this License;
2. authorize a Commercial Engine Offering;
3. transfer ownership of Block Engine;
4. authorize commercial sale of Block Engine as Development Technology; or
5. otherwise grant rights that exceed those granted by this License.

You may license Your own independently created Product Content, API-Based Software, plugins, tools, services, and other original material under terms of Your choice.

Any license You apply to Your own material remains subject to the rights applicable to Block Engine, Original Engine Materials, and Third-Party Materials.

---

## 25. No Patent Grant

No patent license is granted by this License except to the extent a patent license is legally unavoidable to exercise the express rights granted under this License, and except as expressly provided in Section 19 with respect to contributor patent grants.

This License does not grant You ownership of any patent, patent application, or other intellectual property belonging to LeCatMan.

Nothing in this Section limits rights that cannot lawfully be excluded.

---

## 26. Termination

Your rights under this License may terminate upon a material violation.

Where the violation is reasonably capable of being cured, LeCatMan may provide written notice identifying the violation and the action reasonably necessary to cure it.

You will have thirty (30) days from receipt of that notice to cure the violation.

If the violation is not cured within that period, LeCatMan may terminate the rights granted to You.

Where a material violation is not reasonably capable of being cured, termination may occur without a cure period to the extent permitted by applicable law.

**Effect of Termination.** Upon termination, You must cease exercising rights granted under this License, except where applicable law provides otherwise. Specifically, upon termination You may not:

1. distribute new copies or new versions of Products, Mods, or other works containing Engine Materials;
2. publish updates, patches, or expansions to existing Products or Mods that incorporate Engine Materials;
3. onboard new end users to live-service Products through new Engine Material distribution; or
4. continue any activity that constituted the basis for termination.

You may continue to operate live-service Products for end users who received a valid copy before termination, provided that no new Engine Materials are deployed after termination. In-app purchases, subscriptions, and revenue generated through the continued operation of Products already distributed to end users before termination are permitted during a wind-down period not to exceed ninety (90) days from the date of termination, after which continued commercial operation using Engine Materials constitutes a separate violation.

Where immediate termination of live-service operation would cause material harm to end users who have made purchases and have no recourse for refund, You may submit a written request to LeCatMan for an extended wind-down period. LeCatMan is not obligated to grant an extension. The burden rests on the terminated party to demonstrate genuine end-user harm independent of that party's own commercial interests, and any extension granted applies solely to the continued operation of the existing service for existing users and does not authorize new distribution of Engine Materials.

Termination does not invalidate rights lawfully granted to recipients of Products, Mods, plugins, tools, or other works before termination.

Termination does not require a person who lawfully received a Block Engine or Modified Engine distribution before termination to retroactively cease possessing that copy.

Continued use, modification, or redistribution of Block Engine or a Modified Engine remains subject to this License to the extent permitted by applicable law.

Termination of Your rights does not terminate rights independently granted to other persons who are not themselves in violation of this License.

Nothing in this Section creates a continuing right to engage in conduct that was unauthorized before termination.

---

## 27. Disclaimer of Warranty

**THE BLOCK ENGINE IS PROVIDED "AS IS" AND "AS AVAILABLE," WITHOUT WARRANTIES OF ANY KIND, EXPRESS OR IMPLIED, TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW.**

LECATMAN DOES NOT WARRANT THAT BLOCK ENGINE WILL BE ERROR-FREE, SECURE, COMPATIBLE WITH ANY PARTICULAR HARDWARE OR SOFTWARE, OR SUITABLE FOR ANY PARTICULAR PURPOSE.

YOU ACCEPT RESPONSIBILITY FOR DETERMINING WHETHER BLOCK ENGINE IS APPROPRIATE FOR YOUR INTENDED USE.

---

## 28. Limitation of Liability

**TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, LECATMAN AND CONTRIBUTORS TO BLOCK ENGINE SHALL NOT BE LIABLE FOR INDIRECT, INCIDENTAL, SPECIAL, CONSEQUENTIAL, EXEMPLARY, OR PUNITIVE DAMAGES ARISING FROM OR RELATED TO THIS LICENSE OR THE USE OF BLOCK ENGINE.**

**TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE TOTAL AGGREGATE LIABILITY OF LECATMAN ARISING FROM OR RELATED TO THIS LICENSE OR BLOCK ENGINE SHALL NOT EXCEED THE GREATER OF:**

1. the amount actually paid by You to LeCatMan for Block Engine during the twelve (12) months before the event giving rise to the claim; or
2. US $100.

**Equitable Remedies Preserved.** Nothing in this Section limits LeCatMan's right to seek injunctive relief, specific performance, declaratory judgment, account of profits, or other equitable or non-monetary remedies available under applicable law. The monetary limitation in this Section applies to general and consequential damages claims arising under breach of contract theories and does not constitute an election of remedies or a waiver of any equitable or non-monetary remedy. LeCatMan expressly reserves the right to pursue injunctive relief, account of profits, statutory damages under applicable intellectual property law, and any other remedy not expressly limited by the monetary cap in this Section. LeCatMan may pursue monetary, equitable, and statutory remedies jointly, in the alternative, or in any combination permitted by applicable law.

Nothing in this Section excludes liability that cannot legally be excluded or limited, including liability for willful intellectual property infringement to the extent applicable law prohibits such exclusion.

---

## 29. Severability

If any provision of this License is determined to be unenforceable, invalid, or otherwise ineffective, the remaining provisions remain in effect to the maximum extent permitted by applicable law.

Where legally permitted, the affected provision shall be interpreted or modified only to the minimum extent necessary to make it enforceable while preserving its intended purpose.

Invalidity of one application of a provision does not by itself invalidate every other application of that provision.

**Restriction-Grant Linkage.** Notwithstanding the general severability principle of this Section, where Section 7 (Commercial Engine Offerings) or any material restriction of this License is determined to be unenforceable in a jurisdiction, the rights granted under Section 3 with respect to engine distribution and commercial provision of Development Technology are correspondingly limited — to the minimum extent necessary and affecting only the specific conduct that the unenforceable restriction sought to govern — so as to preserve LeCatMan's intended restriction on commercial engine provision in that jurisdiction. This limitation affects only the specific commercial provision activity that was the subject of the unenforceable provision and does not affect other rights granted under Section 3 that are not subject to the unenforceable restriction.

LeCatMan may elect, in lieu of the automatic limitation above, to withdraw this License in the affected jurisdiction entirely and rely exclusively on applicable copyright law and other applicable legal protections with respect to that jurisdiction.

---

## 30. No Waiver

Failure by LeCatMan to enforce a provision of this License does not constitute a waiver of the right to enforce that provision later.

A waiver is effective only where it is: (1) expressly designated as an official Block Engine License waiver; (2) in writing signed by an authorized officer of LeCatMan; and (3) published through a channel expressly designated by LeCatMan as authoritative for official License modifications and waivers.

A waiver concerning one person, transaction, or violation does not automatically constitute a waiver concerning another person, transaction, or violation.

**Official Channel Designation and Notice.** LeCatMan designates its official Block Engine website and repository as the exclusive authoritative channels for official License interpretations, exceptions, and waivers. You are responsible for verifying the official status of any statement before relying on it as an authorized waiver or interpretation. Statements made by LeCatMan through any other channel — including social media accounts, online forums, personal communications, blog posts, videos, podcasts, or informal written communications — do not constitute a waiver of any provision of this License and do not create estoppel, reliance, or any binding modification of this License, regardless of the apparent authority of the speaker. Reliance on unofficial communications as authorization for conduct otherwise prohibited by this License is unreasonable as a matter of this License.

---

## 31. Governing Law and Venue

**Dual License Theory.** This License operates simultaneously as: (1) a contractual license, creating contractual obligations between LeCatMan and You; and (2) a copyright license, constituting an exercise of LeCatMan's rights under applicable copyright law. Where a court determines that this License does not constitute an enforceable contract under applicable law, LeCatMan reserves all rights under applicable copyright law independently of any contractual rights. Conduct that exceeds the scope of this License constitutes copyright infringement under applicable copyright law in addition to, or in the alternative to, breach of contract, at LeCatMan's election in enforcement proceedings.

LeCatMan may pursue both the contractual and copyright theories, whether jointly or in the alternative, in any enforcement proceeding. The assertion of one theory in one proceeding does not constitute a waiver or election against asserting the other theory in any other proceeding or jurisdiction.

**Governing Law.** This License, and claims arising from or relating to it, shall be governed by the laws of the **Hashemite Kingdom of Jordan**, without regard to its conflict-of-law rules, to the maximum extent permitted by applicable law. Where mandatory consumer protection law, intellectual property law, or other applicable mandatory law of another jurisdiction requires a different governing law or forum, this Section applies to the maximum extent permitted by such law.

**Venue.** To the extent permitted by applicable law, disputes arising from or relating to this License shall be brought exclusively in the competent courts of **Amman, Jordan**.

Nothing in this Section prevents either party from seeking urgent or equitable relief in another court where necessary to protect intellectual property rights or other rights that cannot reasonably await ordinary proceedings.

---

## 32. License Versions and Supersession

This License applies to the version of Block Engine distributed with or expressly identified as being governed by this License.

**This Version 5.1 License supersedes and replaces Version 5.0 only for releases of Block Engine that are expressly distributed under Version 5.1.**

**Version 5.1 does not retroactively replace, revoke, modify, or invalidate Version 5.0, Version 4.0, or any other license governing a copy of Block Engine that was lawfully released under that earlier license.**

A person who lawfully obtained a copy of Block Engine under an earlier license continues to be governed by the license that accompanied that copy unless that earlier license expressly provides otherwise or that person separately accepts a different license.

A later version of the Block Engine License does not automatically replace the license applicable to an existing release or previously obtained copy.

A later version applies to a release only where LeCatMan expressly identifies that release as being distributed under the later version.

LeCatMan may publish new versions of this License for future releases of Block Engine.

Unless expressly stated otherwise, a new version does not retroactively alter rights granted under an earlier license.

**No Support Obligation for Version Gaming.** LeCatMan is not obligated to provide updates, security patches, bug fixes, official support, access to official repositories, build tools, or any other benefit to persons who rely on an earlier license version to engage in conduct that would constitute a material violation of this Version 5.1. Nothing in this Section entitles a person to any continued benefit from LeCatMan on the basis of an earlier license version. A person obtaining new releases of Block Engine must comply with the license expressly applicable to those releases.

**Burden of Proof.** Where a person seeks to rely on an earlier license version to engage in conduct not expressly permitted by this Version 5.1, that person bears the burden of demonstrating both: (a) that the specific copy they possess was lawfully obtained under that earlier version; and (b) that the specific conduct they engage in was expressly permitted by the text of that earlier version's terms. Reliance on an earlier version for conduct not expressly permitted by that version's own text, or for conduct that version did not address, does not constitute a valid defense under that earlier version.

---

## 33. Entire Agreement

This License constitutes the complete license governing Block Engine unless supplemented by a separate written agreement signed by LeCatMan.

Any separate Product License, Third-Party Material license, or additional licensing document expressly identified by LeCatMan as applying to a particular component or Product forms a complementary part of the applicable licensing terms.

If a conflict exists between this License and another Block Engine licensing document concerning Block Engine, Engine Materials, Modified Engines, or Block Engine Development Technology, this License controls unless the separate document expressly states that it modifies a specific provision of this License.

Third-Party Material licenses control with respect to the Third-Party Materials to which they apply.

---

## 34. Interpretation Requests

**Submission.** You may submit a written request to LeCatMan through the official Block Engine website or repository for a written interpretation of whether a specific, described activity complies with this License. A valid interpretation request must: (1) describe the proposed activity in sufficient detail to enable evaluation; (2) identify the specific License provisions whose application is in question; and (3) disclose all material facts known to You that bear on the question.

**Response and Reliance.** LeCatMan may, in its discretion, respond to interpretation requests. LeCatMan is not obligated to respond and response times are not guaranteed. Where LeCatMan provides a written interpretation that a described activity complies with this License, and You act in good-faith reliance on that interpretation, LeCatMan may not bring an enforcement action against You for that specific described activity, provided that:

1. the activity You actually performed materially matches the activity as described in the request;
2. You disclosed all material facts relevant to the interpretation at the time of the request;
3. You did not engage in the activity before receiving the interpretation; and
4. LeCatMan has not subsequently issued a revised interpretation covering Your activity.

**Prospective Revision.** LeCatMan may issue a revised interpretation prospectively. A revised interpretation applies only to activity occurring after the revised interpretation is published and does not create liability for activity undertaken in good-faith reliance on the prior interpretation before the revision date.

**Public Interpretations.** LeCatMan may publish redacted interpretations for the general benefit of the developer community. Published interpretations represent LeCatMan's good-faith reading of this License at the time of publication and do not constitute binding legal determinations. Published interpretations may be revised prospectively. A person who did not submit the original request may not rely on a published interpretation as though it were issued specifically to them unless the description in the published interpretation materially matches their own specific circumstances.

**No Obligation.** This Section creates no right to receive an interpretation or to delay compliance with this License pending receipt of one. Submitting an interpretation request does not suspend the application of this License to Your activities.

---

## Practical Interpretation

The following examples illustrate the intended boundary of this License.

### Permitted

A developer may:

* make a game with Block Engine and sell the game;
* make a Mod and sell the Mod;
* make a paid plugin using the Block Engine API;
* make a paid editor extension using the Block Engine API;
* make a paid automation tool for Block Engine;
* make a paid integration between Block Engine and another application;
* make a paid service that uses Block Engine internally;
* use Block Engine for client work;
* modify the engine for their own project;
* fork the engine and distribute the fork for free;
* build an independently created competing engine, including through a documented clean-room process;
* write an independently created implementation compatible with the Block Engine API;
* include necessary API interface material in an independent API client as permitted by this License;
* sell independently created tools that communicate with Block Engine;
* operate a commercial Product that uses Block Engine internally;
* earn advertising, sponsorship, donation, subscription, or sales revenue from a genuine Product;
* include a level editor or proportionate modding tool in a Product for end-user content creation;
* employ or engage contractors to work on their own projects using Block Engine, provided engine access is incidental to directed work;
* host their own Block Engine installation on cloud infrastructure charged at market infrastructure rates;
* submit a contribution to Block Engine and retain ownership of that contribution subject to the contributor license and patent grant.

### Not Permitted

A person may not:

* sell Block Engine itself;
* sell a Modified Engine itself;
* sell a fork as a commercial development engine;
* charge Developers for hosted access to Block Engine as a development platform;
* put Block Engine behind a paid API and sell that engine access;
* disguise Block Engine as a plugin, SDK, editor, library, tool, or service and sell it as Development Technology;
* split Block Engine into several paid components in order to commercially provide the same engine;
* put a nominal game or application around the engine when the real purpose is giving Developers the engine;
* require a paid purchase, subscription, account tier, or service in order to obtain Block Engine or its development functionality;
* use an independently created wrapper as a pretext for commercially providing the engine itself;
* route a prohibited engine offering through affiliates, contractors, subsidiaries, resellers, or multiple services to evade the restrictions;
* call a paid engine distribution a "donation" when payment is actually required;
* make an engine distribution technically free but require payment for the account, repository, installer, service, or other mechanism necessary to obtain it;
* make the free download path deliberately slow, throttled, or obstructed while offering paid fast access;
* provide remote development access to Block Engine while claiming that no copy of the engine is being distributed;
* commercially sublicense Block Engine in a way that removes the restrictions of this License;
* bundle multiple independently created components that together reproduce Block Engine's development functionality and sell that bundle as Development Technology;
* engage contractors and charge them — directly or through the contract structure — for engine access under the guise of a labor arrangement;
* distribute a Modified Engine without including a reasonably prominent notice identifying its derivation from Block Engine;
* contribute code containing a patent claim to Block Engine and later assert that patent against Block Engine users;
* rely on a social media post or informal statement from LeCatMan as authorization for a prohibited activity;
* use automated transpilation or code translation of Block Engine's source to claim an independently created implementation;
* include full engine development tooling in a Product beyond what is proportionate to that Product's specific end-user needs;
* commercially offer a total conversion Mod that itself provides developer tooling enabling others to build new games without separately obtaining Block Engine;
* charge infrastructure rates materially above market rates as a mechanism for collecting consideration for engine access;
* rely on an earlier license version to engage in conduct that version did not expressly permit, or to avoid seeking new releases under this Version 5.1.

### Central Rule

> **You may make money from software made with Block Engine, software that uses Block Engine, software that extends Block Engine, and services that use Block Engine.**
>
> **You may not make money by commercially providing Block Engine itself, a Modified Engine, or Block Engine Development Technology as a development technology.**

> **Important:** This section is provided only as a plain-language explanation and collection of examples. It does **not** replace, modify, expand, restrict, override, supersede, or otherwise alter any provision of the **Block Engine License**.

The **Block Engine License** is the complete and controlling legal document governing Block Engine. In the event of any inconsistency, conflict, ambiguity, or difference between this section and the Block Engine License, the **Block Engine License controls and takes precedence in all circumstances**.

Nothing in this section creates an additional license, restriction, permission, obligation, warranty, promise, or contractual term beyond those contained in the Block Engine License.

---

**Copyright © 2026 LeCatMan. All rights reserved.**

**Block Engine License Version 5.1 — September 2026**