// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 6783 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=6783
//
// <-- Short Description -->
// Solving a system of linear equation by backslash ("\") will cause a crash to Scilab 5.2.1, when using complex numbers.

// Replication Code
S=[
1.3     24      4.1     29      0.9     33
0.6     258     0.7     265     0.2     39
0.5     2       1.4     351     0.5     323
0.7     63      1.2     19      0.4     318
17.0    152     29.0    196     6.0     232
23.0    18      40.0    62      14.0    104
8.0     213     20.0    177     8.0     147
12.0    106     26.0    45      11.0    21
8.1     25      6.4     182     6.9     203
2.0     282     2.5     20      1.5     114
5.9     215     5.6     34      4.6     25
3.7     185     3.6     5       2.8     9
27.0    134     30.0    290     18.0    321
23.0    17      26.0    151     9.0     220
34.0    330     26.0    164     24.0    140
33.0    187     20.0    18      24.0    350
2.4     50      3.8     157     3.6     289
2.2     281     3.7     57      3.0     187
4.5     322     5.9     149     1.1     48
1.6     249     3.1     62      1.3     239
13.0    152     18.0    286     24.0    52
21.0    77      16.0    166     47.0    298
41.0    48      34.0    239     4.0     140
80.0    301     67.0    120     10.0    81
3.7     43      2.6     215     5.4     290
3.3     284     3.6     66      3.4     196
5.6     340     3.7     172     2.1     342
2.6     272     2.3     72      2.3     274
34.0    154     23.0    332     32.0    47
29.0    56      13.0    209     59.0    299
43.0    62      39.0    241     13.0    89
91.0    309     75.0    131     15.0    321
];


S0=[2.3 278
0.4     266
1.1     270
0       0
29      141
21      32
16      97
16      4
5.9     132
0.3     0
5.4     327
3.8     313
40      244
12      75
47      101
38      343
1.6     337
1.5     281
5.9     34
2.5     310
8       37
8       320
32      134
67      29
2.3     5
2       307
7.4     43
3.2     320
4       0
10      357
34      128
81      26
];

S02=[0.85       258
0.26    0
0.33    226
0.04    0
14.43   71
11.48   294
14.19   65
16.00   311
1.74    345
0.70    178
2.35    191
1.74    170
9.18    105
4.27    289
10.32   356
4.75    0
2.97    215
2.87    126
5.14    242
4.75    149
14.98   327
11.71   193
10.32   323
14.82   190
2.60    100
2.10    43
3.40    152
3.00    65
23.00   287
21.00   111
22.00   229
52.00   99
];


fac=[10
10
10
10
1
1
1
1
10
10
10
10
1
1
1
1
30
30
30
30
2
2
2
2
80
80
80
80
4
4
4
4];

if isdef('without')==%T;
S(without:8:$,:)=[];
S0(without:8:$,:)=[];
fac(without:8:$,:)=[];
else
end

S0_a=fac.*S0(:,1);
S0_w=S0(:,2).*%pi/180;
S0c=S0_a.*exp(%i*S0_w);
S0_c2=S0(:,1).*exp(%i*S0_w); // ohne Faktor!!!!

S02_a=fac.*S02(:,1);
S02_w=S02(:,2).*%pi/180;
S02c=S02_a.*exp(%i*S02_w);
S02_c2=S02(:,1).*exp(%i*S02_w); // ohne Faktor


S_a=S(:,1:2:$).*[fac fac fac];
S_wdeg=S(:,2:2:$);
S_w=S_wdeg*%pi/180;

M_test=[1000       0            0         0              0      0         760   258
            0     0         1000          0          0     0           0     0
            0     0             0         0           1000         0         760   210];

M_a=M_test(:,1:2:$);
M_wdeg=M_test(:,2:2:$);
M_w=M_wdeg*%pi/180;

Sc=[S_a.*exp(%i*S_w) S02c-S0c];
Mc=M_a.*exp(%i*M_w);

ierr = execstr("C=Mc''\Sc''","errcatch");
if ierr <> 0 then pause,end
if size(C) <> [3 32] then pause,end