pdfcontent = [
  'pages/users-guide/UsersGuide.rst',
  'pages/python-tutorial/PythonTutorial.rst',
  'pages/python-cpp/PythonCpp.rst',
  'pages/design-flow/DesignFlow.rst',
  'pages/stratus/Stratus.rst',
  'pages/check-toolkit/CheckToolkit.rst',
  'pages/rds/RDS.rst',
]


rstcontent = files(
  'etc/definitions.rst',
  'pages/design-flow/DesignFlow_HTML.rst',
  'pages/design-flow/QuickStart.rst',
  'index.rst',
  'pages/gitlab.rst',
  'pages/homepage.rst',
  'pages/python-cpp/Configuration.rst',
  'pages/python-cpp/DBoHierarchy.rst',
  'pages/python-cpp/DBoStandalone.rst',
  'pages/python-cpp/DbU.rst',
  'pages/python-cpp/Introduction.rst',
  'pages/python-cpp/Name.rst',
  'pages/python-cpp/NonDBo.rst',
  'pages/python-cpp/PythonCpp_HTML.rst',
  'pages/python-tutorial/AdvancedTopics.rst',
  'pages/python-tutorial/CellNetComponent.rst',
  'pages/python-tutorial/CgtScript.rst',
  'pages/python-tutorial/Collections.rst',
  'pages/python-tutorial/Environment.rst',
  'pages/python-tutorial/Introduction.rst',
  'pages/python-tutorial/Netlist.rst',
  'pages/python-tutorial/PythonTutorial_HTML.rst',
  'pages/python-tutorial/RealDesigns.rst',
  'pages/python-tutorial/ToolEngines.rst',
  'pages/rds/RDS_HTML.rst',
  'pages/presentations/PresentationsPage.rst',
  'pages/presentations/Presentations_HTML.rst',
  'pages/rds/RDSpage.rst',
  'pages/stratus/Developper.rst',
  'pages/stratus/DpGen.rst',
  'pages/stratus/Language.rst',
  'pages/stratus/Patterns.rst',
  'pages/stratus/Stratus_HTML.rst',
  'pages/symbolic-layout.rst',
  'pages/packaging/OBS.rst',
  'pages/packaging/Packaging_HTML.rst',
  'pages/technical-log/TechnicalLog_HTML.rst',
  'pages/technical-log/December_2023.rst',
  'pages/users-guide/Configuration.rst',
  'pages/users-guide/DesignFlow.rst',
  'pages/users-guide/Installation.rst',
  'pages/users-guide/LicenseCredits.rst',
  'pages/users-guide/Releases.rst',
  'pages/users-guide/ScriptsPlugins.rst',
  'pages/users-guide/UsersGuide_HTML.rst',
  'pages/users-guide/ViewerTools.rst',
)

css = files(
  'themes/nest-coriolis/static/css/nest.css',
  'themes/nest-coriolis/static/css/pygment.css',
  'themes/nest-coriolis/static/css/coriolis.css',
)

plugins = files(
  'pelican-plugins/bootstrap-rst/140x140.png',
  'pelican-plugins/bootstrap-rst/171x180.png',
  'pelican-plugins/bootstrap-rst/300x200.png',
  'pelican-plugins/bootstrap-rst/__init__.py',
  'pelican-plugins/bootstrap-rst/bootstrap.py',
  'pelican-plugins/bootstrap-rst/custom.css',
  'pelican-plugins/bootstrap-rst/directives.py',
  'pelican-plugins/bootstrap-rst/docs-min.css',
  'pelican-plugins/bootstrap-rst/make-glyphicons.py',
  'pelican-plugins/bootstrap-rst/page.tmpl',
  'pelican-plugins/bootstrap-rst/pygments.css',
  'pelican-plugins/bootstrap-rst/roles.py',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap-theme.css',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap-theme.css.map',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap-theme.min.css',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap.css',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap.css.map',
  'pelican-plugins/bootstrap-rst/bootstrap/css/bootstrap.min.css',
  'pelican-plugins/bootstrap-rst/bootstrap/fonts/glyphicons-halflings-regular.eot',
  'pelican-plugins/bootstrap-rst/bootstrap/fonts/glyphicons-halflings-regular.svg',
  'pelican-plugins/bootstrap-rst/bootstrap/fonts/glyphicons-halflings-regular.ttf',
  'pelican-plugins/bootstrap-rst/bootstrap/fonts/glyphicons-halflings-regular.woff',
  'pelican-plugins/bootstrap-rst/bootstrap/js/bootstrap.js',
  'pelican-plugins/bootstrap-rst/bootstrap/js/bootstrap.min.js',
)

dopdf = find_program('etc/doPdf.sh')

#pdf_documents = []
#foreach document : pdfcontent
#    basename = document.split( '/' )[ -1 ].replace( '.rst', '' )
#    pdf_documents += custom_target( basename + '_pdf'
#                                  , command: [ dopdf
#    			                 , '--buildDir=@0@'.format( meson.current_build_dir() )
#    			                 , '--sourceDir=@0@'.format( meson.current_source_dir() )
#                                         , '--stylesheet=etc/SoC-ReST.tex'
#    			                 , '--rst2latex=@0@'.format( rst2latex.full_path() )
#    			                 , '--pdflatex=@0@'.format( pdflatex.full_path() )
#    			                 , document ]
#                                  , input:       document
#                                  , output:      basename + '.pdf'
#                                  , install:     true
#                                  , install_dir: pdfdir
#                                  )
#endforeach


cdata = configuration_data()
cdata.set('SOURCEDIR'  , meson.current_source_dir())
cdata.set('OUTPUT_PATH', meson.current_build_dir())
cdata.set('SITEURL'    , docsiteurl )
pelicanconf = configure_file( input:        'pelicanconf.py.in'
                            , output:       'pelicanconf.py'
                            , configuration: cdata
                            , install:       false
                            )

htmldoc = custom_target( 'htmldoc'
                       , output: [ 'archives.html'
                                 , 'authors.html'
                                 , 'categories.html'
                                 , 'images'
                                 , 'index.html'
                                 , 'pages'
                                 , 'pdfs'
                                 , 'tags.html'
                                 , 'theme'
                                 ]
                       , depend_files: [ rstcontent, css, plugins, pelicanconf ]
		      #, depends: [ pdf_documents ]
		       , depends: [ ]
                       , command: [ pelican
                                  , '-vD'
                                  , '--ignore-cache'
                                  , '-s'
                                  , pelicanconf
                                  , meson.current_source_dir()/'content'
				  ]
                       , install: true
                       , install_dir: htmldir
                       )

docs = run_target( 'docs'
                 , command: 'true'
                 , depends: [ htmldoc
		            , crlcore_docs
			    , analog_docs
			    , hurricane_docs
			    , viewer_docs
			    , oroshi_docs
			    , unicorn_docs
			    ]
                 )

install_data( install_dir: pdfdir
            , sources:     files('content/pdfs/SAL.Bootcamp.pdf') )
