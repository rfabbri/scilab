mode(-1)
// Copyright INRIA

if ~with_pvm() then
  messagebox('Sorry this version has not been built with pvm interface',"modal","error");
  return
end

if getos() == 'Windows' then

	mes=messagebox(['This demo recquires rsh or ssh client/server on Windows.' ..
	'Click on Cancel, if you aren''t sure to have it.' ..
	'' ..
	'Scilab may be unstable if you haven''t rsh/ssh.' ..
	'' ..
	'Before using PVM, you should test the functionality of the additional software, e.g.' ..
  '' ..  
  '""rsh localhost -l login dir | more""' ..
  '' ..  
  'This should show the directory listing of the local host.' ..
  'Piping to ""more"" additionally checks for buffered std{io,err}.'],"modal","info",['Ok','Cancel'])
	if mes == 2 then return, end
	
	if getenv('PVM_RSH','') == '' then
	  // PVM_RSH not defined then no demos
	  return
	end
end

demos_name=[
    'Master and slave'
    ]
exec('SCI/modules/pvm/demos/pvm1.sce');
return
while %t do
  n=x_choose(demos_name,'Choose a demo')
  select n
  case 0 then 
    break
  case 1 then  
    exec('SCI/modules/pvm/demos/pvm1.sce');

  end
end