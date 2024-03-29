// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- TEST WITH GRAPHIC -->

// Unit test for barhomogenize

subplot(2,3,1);
xtitle('ex1: creation of 1 yellow bar and  3 bars');
x=1:3; y1=1:3; y2=[4 3 5;6 7 8;9 10 11];
bar(x,y1,'yellow');bar(x,y2);

subplot(2,3,2);
xtitle('grouped homogenisation');
x=1:3; y1=1:3; y2=[4 3 5;6 7 8;9 10 11];
bar(x,y1,'yellow');bar(x,y2);
barhomogenize();

subplot(2,3,3);
xtitle('stacked homogenisation');
x=1:3; y1=1:3; y2=[4 3 5;6 7 8;9 10 11];
bar(x,y1,'yellow');bar(x,y2);
barhomogenize('stacked',1);

f=gcf();
a1=f.children(1);
a2=f.children(2);
a3=f.children(3);
c11=a1.children(1);
c12=a1.children(2);
c21=a2.children(1);
c22=a2.children(2);
c31=a3.children(1);
c32=a3.children(2);
// Third graphic: stacked
p111=c11.children(1); // red polyline
p112=c11.children(2); // green polyline
p113=c11.children(3); // blue polyline
p121=c12.children(1); // yellow polyline
// Second graphic: grouped
p211=c21.children(1); // red polyline
p212=c21.children(2); // green polyline
p213=c21.children(3); // blue polyline
p221=c22.children(1); // yellow polyline
// First graphic: no homogenized
p311=c31.children(1); // red polyline
p312=c31.children(2); // green polyline
p313=c31.children(3); // blue polyline
p321=c32.children(1); // yellow polyline


// Check First graphic axes
assert_checkequal(a3.x_location, "bottom");
assert_checkequal(a3.y_location, "left");
assert_checkequal(a3.auto_ticks, ["off", "on", "on"]);
assert_checkequal(a3.x_ticks.locations, [1;2;3]);
assert_checkequal(a3.y_ticks.locations, [0;2;4;6;8;10;12]);
assert_checkequal(a3.z_ticks.locations, []);
assert_checkequal(a3.x_ticks.labels, ["1";"2";"3"]);
assert_checkequal(a3.y_ticks.labels, ["0";"2";"4";"6";"8";"10";"12"]);
assert_checkequal(a3.z_ticks.labels, []);
assert_checkequal(a3.sub_ticks, [0,1]);
assert_checktrue(abs(a3.data_bounds - [0.55,0;3.45,11]) < 0.05);
assert_checkequal(a3.margins, [0.125,0.125,0.125,0.125]);
assert_checktrue(abs(a3.axes_bounds - [0,0,0.3333333333,0.5]) < 0.0005);

// Check Second 
assert_checkequal(a2.x_location, a3.x_location);
assert_checkequal(a2.y_location, a3.y_location);
assert_checkequal(a2.auto_ticks, a3.auto_ticks);
assert_checkequal(a2.x_ticks.locations, a3.x_ticks.locations);
assert_checkequal(a2.y_ticks.locations, a3.y_ticks.locations);
assert_checkequal(a2.z_ticks.locations, a3.z_ticks.locations);
assert_checkequal(a2.x_ticks.labels, a3.x_ticks.labels);
assert_checkequal(a2.y_ticks.labels, a3.y_ticks.labels);
assert_checkequal(a2.z_ticks.labels, a3.z_ticks.labels);
assert_checkequal(a2.sub_ticks, a3.sub_ticks);
assert_checktrue(abs(a2.data_bounds - a3.data_bounds) < 0.05);
assert_checkequal(a2.margins, a3.margins);
assert_checktrue(abs(a2.axes_bounds - a3.axes_bounds) < 0.5);

// Check third
assert_checkequal(a1.x_location, a3.x_location);
assert_checkequal(a1.y_location, a3.y_location);
assert_checkequal(a1.auto_ticks, a3.auto_ticks);
assert_checkequal(a1.x_ticks.locations, a3.x_ticks.locations);
assert_checkequal(a1.y_ticks.locations, [0;5;10;15;20;25;30;35]);
assert_checkequal(a1.z_ticks.locations, a3.z_ticks.locations);
assert_checkequal(a1.x_ticks.labels, a3.x_ticks.labels);
assert_checkequal(a1.y_ticks.labels, ["0";"5";"10";"15";"20";"25";"30";"35"]);
assert_checkequal(a1.z_ticks.labels, a3.z_ticks.labels);
assert_checkequal(a1.sub_ticks, a3.sub_ticks);
assert_checktrue(abs(a1.data_bounds - [0.55,0;3.45,33]) < 0.05);
assert_checkequal(a1.margins, a3.margins);
assert_checktrue(abs(a1.axes_bounds - [0.6666667,0,0.3333333,0.5]) < 0.05);

// Check polylines of first graphic
assert_checkequal(p311.data, [1,5;2,8;3,11]);
assert_checkequal(p311.line_style, 1);
assert_checkequal(p311.polyline_style, 6);
assert_checkequal(p311.foreground, -1);
assert_checkequal(p311.background, 5);
assert_checkequal(p311.mark_mode, "off");
assert_checkequal(p311.mark_style, 0);
assert_checkequal(p311.mark_size_unit, "point");
assert_checkequal(p311.mark_size, 0);
assert_checkequal(p311.mark_foreground, -1);
assert_checkequal(p311.mark_background, -2);
assert_checkequal(p311.x_shift, [0.3,0.3,0.3]);
assert_checkequal(p311.y_shift, []);
assert_checkalmostequal(p311.bar_width, 0.24);

assert_checkequal(p312.data, [1,3;2,7;3,10]);
assert_checkequal(p312.line_style, 1);
assert_checkequal(p312.polyline_style, 6);
assert_checkequal(p312.foreground, -1);
assert_checkequal(p312.background, 33);
assert_checkequal(p312.mark_mode, "off");
assert_checkequal(p312.mark_style, 0);
assert_checkequal(p312.mark_size_unit, "point");
assert_checkequal(p312.mark_size, 0);
assert_checkequal(p312.mark_foreground, -1);
assert_checkequal(p312.mark_background, -2);
assert_checkequal(p312.x_shift, [0,0,0]);
assert_checkequal(p312.y_shift, []);
assert_checkalmostequal(p312.bar_width, 0.24);

assert_checkequal(p313.data, [1,4;2,6;3,9]);
assert_checkequal(p313.line_style, 1);
assert_checkequal(p313.polyline_style, 6);
assert_checkequal(p313.foreground, -1);
assert_checkequal(p313.background, 2);
assert_checkequal(p313.mark_mode, "off");
assert_checkequal(p313.mark_style, 0);
assert_checkequal(p313.mark_size_unit, "point");
assert_checkequal(p313.mark_size, 0);
assert_checkequal(p313.mark_foreground, -1);
assert_checkequal(p313.mark_background, -2);
assert_checkequal(p313.x_shift, [-0.3,-0.3,-0.3]);
assert_checkequal(p313.y_shift, []);
assert_checkalmostequal(p313.bar_width, 0.24);

assert_checkequal(p321.data, [1,1;2,2;3,3]);
assert_checkequal(p321.line_style, 1);
assert_checkequal(p321.polyline_style, 6);
assert_checkequal(p321.foreground, -1);
assert_checkequal(p321.background, 7);
assert_checkequal(p321.mark_mode, "off");
assert_checkequal(p321.mark_style, 0);
assert_checkequal(p321.mark_size_unit, "point");
assert_checkequal(p321.mark_size, 0);
assert_checkequal(p321.mark_foreground, -1);
assert_checkequal(p321.mark_background, -2);
assert_checkequal(p321.x_shift, [0,0,0]);
assert_checkequal(p321.y_shift, []);
assert_checkalmostequal(p321.bar_width, 0.8);

// Check polylines of second graphic
assert_checkequal(p211.data, p311.data);
assert_checkequal(p211.line_style, p311.line_style);
assert_checkequal(p211.polyline_style, p311.polyline_style);
assert_checkequal(p211.foreground, p311.foreground);
assert_checkequal(p211.background, p311.background);
assert_checkequal(p211.mark_mode, p311.mark_mode);
assert_checkequal(p211.mark_style, p311.mark_style);
assert_checkequal(p211.mark_size_unit, p311.mark_size_unit);
assert_checkequal(p211.mark_size, p311.mark_size);
assert_checkequal(p211.mark_foreground, p311.mark_foreground);
assert_checkequal(p211.mark_background, p311.mark_background);
assert_checkequal(p211.x_shift, [-0.3375,-0.3375,-0.3375]);
assert_checkequal(p211.y_shift, [0,0,0]);
assert_checkalmostequal(p211.bar_width, 0.18);

assert_checkequal(p212.data, p312.data);
assert_checkequal(p212.line_style, p312.line_style);
assert_checkequal(p212.polyline_style, p312.polyline_style);
assert_checkequal(p212.foreground, p312.foreground);
assert_checkequal(p212.background, p312.background);
assert_checkequal(p212.mark_mode, p312.mark_mode);
assert_checkequal(p212.mark_style, p312.mark_style);
assert_checkequal(p212.mark_size_unit, p312.mark_size_unit);
assert_checkequal(p212.mark_size, p312.mark_size);
assert_checkequal(p212.mark_foreground, p312.mark_foreground);
assert_checkequal(p212.mark_background, p312.mark_background);
assert_checkequal(p212.x_shift, [-0.1125,-0.1125,-0.1125]);
assert_checkequal(p212.y_shift, p211.y_shift);
assert_checkalmostequal(p212.bar_width, p211.bar_width);

assert_checkequal(p213.data, p313.data);
assert_checkequal(p213.line_style, p313.line_style);
assert_checkequal(p213.polyline_style, p313.polyline_style);
assert_checkequal(p213.foreground, p313.foreground);
assert_checkequal(p213.background, p313.background);
assert_checkequal(p213.mark_mode, p313.mark_mode);
assert_checkequal(p213.mark_style, p313.mark_style);
assert_checkequal(p213.mark_size_unit, p313.mark_size_unit);
assert_checkequal(p213.mark_size, p313.mark_size);
assert_checkequal(p213.mark_foreground, p313.mark_foreground);
assert_checkequal(p213.mark_background, p313.mark_background);
assert_checkequal(p213.x_shift, [0.1125,0.1125,0.1125]);
assert_checkequal(p213.y_shift, p211.y_shift);
assert_checkalmostequal(p213.bar_width, p211.bar_width);

assert_checkequal(p221.data, p321.data);
assert_checkequal(p221.line_style, p321.line_style);
assert_checkequal(p221.polyline_style, p321.polyline_style);
assert_checkequal(p221.foreground, p321.foreground);
assert_checkequal(p221.background, p321.background);
assert_checkequal(p221.mark_mode, p321.mark_mode);
assert_checkequal(p221.mark_style, p321.mark_style);
assert_checkequal(p221.mark_size_unit, p321.mark_size_unit);
assert_checkequal(p221.mark_size, p321.mark_size);
assert_checkequal(p221.mark_foreground, p321.mark_foreground);
assert_checkequal(p221.mark_background, p321.mark_background);
assert_checkequal(p221.x_shift, [0.3375,0.3375,0.3375]);
assert_checkequal(p221.y_shift, p211.y_shift);
assert_checkalmostequal(p221.bar_width, p211.bar_width);

// Check polylines of third graphic
assert_checkequal(p111.data, p311.data);
assert_checkequal(p111.line_style, p311.line_style);
assert_checkequal(p111.polyline_style, p311.polyline_style);
assert_checkequal(p111.foreground, p311.foreground);
assert_checkequal(p111.background, p311.background);
assert_checkequal(p111.mark_mode, p311.mark_mode);
assert_checkequal(p111.mark_style, p311.mark_style);
assert_checkequal(p111.mark_size_unit, p311.mark_size_unit);
assert_checkequal(p111.mark_size, p311.mark_size);
assert_checkequal(p111.mark_foreground, p311.mark_foreground);
assert_checkequal(p111.mark_background, p311.mark_background);
assert_checkequal(p111.x_shift, [0,0,0]);
assert_checkequal(p111.y_shift, [0,0,0]);
assert_checkalmostequal(p111.bar_width, 0.9);

assert_checkequal(p112.data, p312.data);
assert_checkequal(p112.line_style, p312.line_style);
assert_checkequal(p112.polyline_style, p312.polyline_style);
assert_checkequal(p112.foreground, p312.foreground);
assert_checkequal(p112.background, p312.background);
assert_checkequal(p112.mark_mode, p312.mark_mode);
assert_checkequal(p112.mark_style, p312.mark_style);
assert_checkequal(p112.mark_size_unit, p312.mark_size_unit);
assert_checkequal(p112.mark_size, p312.mark_size);
assert_checkequal(p112.mark_foreground, p312.mark_foreground);
assert_checkequal(p112.mark_background, p312.mark_background);
assert_checkequal(p112.x_shift, [0,0,0]);
assert_checkequal(p112.y_shift, [5,8,11]);
assert_checkalmostequal(p112.bar_width, p111.bar_width);

assert_checkequal(p113.data, p313.data);
assert_checkequal(p113.line_style, p313.line_style);
assert_checkequal(p113.polyline_style, p313.polyline_style);
assert_checkequal(p113.foreground, p313.foreground);
assert_checkequal(p113.background, p313.background);
assert_checkequal(p113.mark_mode, p313.mark_mode);
assert_checkequal(p113.mark_style, p313.mark_style);
assert_checkequal(p113.mark_size_unit, p313.mark_size_unit);
assert_checkequal(p113.mark_size, p313.mark_size);
assert_checkequal(p113.mark_foreground, p313.mark_foreground);
assert_checkequal(p113.mark_background, p313.mark_background);
assert_checkequal(p113.x_shift, [0,0,0]);
assert_checkequal(p113.y_shift, [8,15,21]);
assert_checkalmostequal(p113.bar_width, p111.bar_width);

assert_checkequal(p121.data, p321.data);
assert_checkequal(p121.line_style, p321.line_style);
assert_checkequal(p121.polyline_style, p321.polyline_style);
assert_checkequal(p121.foreground, p321.foreground);
assert_checkequal(p121.background, p321.background);
assert_checkequal(p121.mark_mode, p321.mark_mode);
assert_checkequal(p121.mark_style, p321.mark_style);
assert_checkequal(p121.mark_size_unit, p321.mark_size_unit);
assert_checkequal(p121.mark_size, p321.mark_size);
assert_checkequal(p121.mark_foreground, p321.mark_foreground);
assert_checkequal(p121.mark_background, p321.mark_background);
assert_checkequal(p121.x_shift, [0,0,0]);
assert_checkequal(p121.y_shift, [12,21,30]);
assert_checkalmostequal(p121.bar_width, p111.bar_width);
