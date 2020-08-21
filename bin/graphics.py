
# Python script to manage the graphical outputs produced by EntoSim

# Created by Luca Rossini on 11/08/2020
# email: luca.rossini@unitus.it
# last update 21/08/2020


import plotly as py
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from scipy import stats
import numpy as np
import pandas as pd
import dash
import os
import dash_core_components as dcc
import dash_html_components as html
import dash_bootstrap_components as dbc

host='0.0.0.0'
port='8080'


# This function provides the results of Logan fit

def grafico_logan():
    
    os.system('echo "grafico_logan() -python- function started " >> ../logfile.log')
    
    app = dash.Dash()
    
    # Read the experimental life tables
    LifeTables = pd.read_csv("../input/LifeTablesRates.txt", sep="\t", header=None)
    
    # Set the header of the experimental life tables
    LifeTables.columns = ["Temp", "DevRate", "Temp_Err", "DevRate_Err"]
    
    # Import the best fit parameters and errors calculated by 'fittasso'
    BestFitPar = pd.read_csv("../input/.RatePar-simulator/logratepar.txt", sep="\t", header=None)
    BestFitPar.columns = ["Par", "Par_Err"]
    
    # Array with the best fit parameters and their error
    FuncPar = BestFitPar['Par']
    FuncParErr = BestFitPar['Par_Err']
    
    # Definition of Logan function and interval plot
    T = np.linspace(0, FuncPar[2], 100)
    
    LogFunc = FuncPar[0] * (np.exp(FuncPar[1] * T) - np.exp((FuncPar[1] * FuncPar[2]) - ((FuncPar[2] - T)/FuncPar[3])))
    
    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=LifeTables['Temp'],
        y=LifeTables['DevRate'],
        mode='markers',
        name='Experimental life tables',
        showlegend=True,
        error_y=dict(
            type='data',
            array=LifeTables['DevRate_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        error_x=dict(
            type='data',
            array=LifeTables['Temp_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        marker=dict(
            color='purple',
            size=7
            ),
    )
    
    # Second plot: add the best fit function
    trace_LogFunc = go.Scatter(
        x=T,
        y=LogFunc,
        name='Logan best fit function'
    )
    
    
    fig = go.Figure(data=[trace_points, trace_LogFunc])
    
    # Set plot title and layout
    fig.update_layout(
        title='Logan development rate function fit results',
        yaxis_title='Development rate (1/d)',
        xaxis_title='Temperature (C)',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return


# This function provides the results of Briere fit

def grafico_briere():
    
    os.system('echo "grafico_briere() -python- function started " >> ../logfile.log')
	
    app = dash.Dash()    

    # Read the experimental life tables
    LifeTables = pd.read_csv("../input/LifeTablesRates.txt", sep="\t", header=None)
    
    # Set the header of the experimental life tables
    LifeTables.columns = ["Temp", "DevRate", "Temp_Err", "DevRate_Err"]
    
    # Import the best fit parameters and errors calculated by 'fittasso'
    BestFitPar = pd.read_csv("../input/.RatePar-simulator/briratepar.txt", sep="\t", header=None)
    BestFitPar.columns = ["Par", "Par_Err"]
    
    # Array with the best fit parameters and their error
    FuncPar = BestFitPar['Par']
    FuncParErr = BestFitPar['Par_Err']
    
    # Definition of Briere function and interval plot
    T = np.linspace(FuncPar[1], FuncPar[2], 100)
    
    BriFunc = FuncPar[0] * T * (T - FuncPar[1]) * pow((FuncPar[2] - T), (1 / FuncPar[3]))
    
    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=LifeTables['Temp'],
        y=LifeTables['DevRate'],
        mode='markers',
        name='Experimental life tables',
        showlegend=True,
        error_y=dict(
            type='data',
            array=LifeTables['DevRate_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        error_x=dict(
            type='data',
            array=LifeTables['Temp_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        marker=dict(
            color='purple',
            size=7
            ),
    )
    
    # Second plot: add the best fit function
    trace_BriFunc = go.Scatter(
        x=T,
        y=BriFunc,
        name='Briere best fit function'
    )
    
    
    fig = go.Figure(data=[trace_points, trace_BriFunc])
    
    # Set plot title and layout
    fig.update_layout(
        title='Briere development rate function fit results',
        yaxis_title='Development rate (1/d)',
        xaxis_title='Temperature (C)',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return


# This function provides the results of linear fit

def grafico_lineare():
    
    os.system('echo "grafico_lineare() -python- function started " >> ../logfile.log')
    
    app = dash.Dash()

    # Read the experimental life tables
    LifeTables = pd.read_csv("../input/LifeTablesRates.txt", sep="\t", header=None)
    
    # Set the header of the experimental life tables
    LifeTables.columns = ["Temp", "DevRate", "Temp_Err", "DevRate_Err"]
    
    # Import the best fit parameters and errors calculated by 'fittasso'
    BestFitPar = pd.read_csv("../input/.RatePar-simulator/linratepar.txt", sep="\t", header=None)
    BestFitPar.columns = ["Par", "Par_Err"]
    
    # Array with the best fit parameters and their error
    FuncPar = BestFitPar['Par']
    FuncParErr = BestFitPar['Par_Err']
    
    # Definition of Linear function and interval plot
    T = np.linspace(0, 45, 100)
    
    LinFunc = FuncPar[0] * T + FuncPar[1]
    
    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=LifeTables['Temp'],
        y=LifeTables['DevRate'],
        mode='markers',
        name='Experimental life tables',
        showlegend=True,
        error_y=dict(
            type='data',
            array=LifeTables['DevRate_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        error_x=dict(
            type='data',
            array=LifeTables['Temp_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        marker=dict(
            color='purple',
            size=7
            ),
    )
    
    # Second plot: add the best fit function
    trace_LinFunc = go.Scatter(
        x=T,
        y=LinFunc,
        name='Linear best fit function'
    )
    
    
    fig = go.Figure(data=[trace_points, trace_LinFunc])
    
    # Set plot title and layout
    fig.update_layout(
        title='Linear development rate function fit results',
        yaxis_title='Development rate (1/d)',
        xaxis_title='Temperature (C)',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return


# This function provides the results of Sharpe and De Michele fit

def grafico_sdm():
    
    os.system('echo "grafico_sdm() -python- function started " >> ../logfile.log')
    
    app = dash.Dash()
    
    # Read the experimental life tables
    LifeTables = pd.read_csv("../input/LifeTablesRates.txt", sep="\t", header=None)
    
    # Set the header of the experimental life tables
    LifeTables.columns = ["Temp", "DevRate", "Temp_Err", "DevRate_Err"]
    
    # Import the best fit parameters and errors calculated by 'fittasso'
    BestFitPar = pd.read_csv("../input/.RatePar-simulator/SDMratepar.txt", sep="\t", header=None)
    BestFitPar.columns = ["Par", "Par_Err"]
    
    # Array with the best fit parameters and their error
    FuncPar = BestFitPar['Par']
    FuncParErr = BestFitPar['Par_Err']
    
    # Definition of Sharpe and De Michele function and interval plot
    T = np.linspace(0, 45, 100)
    
    SDMFunc = (T * np.exp(FuncPar[0] - (FuncPar[1] / T))) / (1 + np.exp(FuncPar[2] - (FuncPar[3] / T)) + np.exp(FuncPar[4] - (FuncPar[5] / T)))
    
    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=LifeTables['Temp'],
        y=LifeTables['DevRate'],
        mode='markers',
        name='Experimental life tables',
        showlegend=True,
        error_y=dict(
            type='data',
            array=LifeTables['DevRate_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        error_x=dict(
            type='data',
            array=LifeTables['Temp_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        marker=dict(
            color='purple',
            size=7
            ),
    )
    
    # Second plot: add the best fit function
    trace_SDMFunc = go.Scatter(
        x=T,
        y=SDMFunc,
        name='Sharpe and De Michele best fit function'
    )
    
    
    fig = go.Figure(data=[trace_points, trace_SDMFunc])
    
    # Set plot title and layout
    fig.update_layout(
        title='Sharpe and De Michele development rate function fit results',
        yaxis_title='Development rate (1/d)',
        xaxis_title='Temperature (C)',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return

# Makes a QQ-plot of a single comparison in validator_single

def QQ_single_validation():

    os.system('echo "QQ_single_validation() -python- function started " >> ../logfile.log')

    app = dash.Dash()

    # Read the data to plot
    QQplot = pd.read_csv("../input/.validator/QQplot.txt", sep="\t", header=None)

    # Set the header of the experimental life tables
    QQplot.columns = ["Sim", "Valid"]
    
    # Fit data with a linear function
    slope, intercept, r_value, p_value, std_err = stats.linregress(QQplot['Sim'], QQplot['Valid'])
    line = slope * QQplot['Sim'] + intercept

    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=QQplot['Sim'],
        y=QQplot['Valid'],
        mode='markers',
        name='QQ-scores',
        marker=dict(
            color='purple',
            size=7
            ),
    )

    trace_linfit = go.Scatter(
        x=QQplot['Sim'],
        y=line,
        mode='lines',
        name ='Bisector',
    )
    
    fig = go.Figure(data=[trace_points, trace_linfit])

    # Set plot title and layout
    fig.update_layout(
        title='QQplot: simulation vs field data',
        yaxis_title='Field data',
        xaxis_title='Simulated data - Or best fit curve',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )

    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )

    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )

    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=False, use_reloader=False)
    
    return


# Plot the development rate functions overlapped

def ratefunctionresume():
    
    os.system('echo "ratefunctionresume() -python- function started " >> ../logfile.log')
    
    app = dash.Dash()	
	
    # Read the experimental life tables
    LifeTables = pd.read_csv("../input/LifeTablesRates.txt", sep="\t", header=None)
    
    # Set the header of the experimental life tables
    LifeTables.columns = ["Temp", "DevRate", "Temp_Err", "DevRate_Err"]
    
    # First plot: life tables with errors
    trace_points = go.Scatter(
        x=LifeTables['Temp'],
        y=LifeTables['DevRate'],
        mode='markers',
        name='Experimental life tables',
        showlegend=True,
        error_y=dict(
            type='data',
            array=LifeTables['DevRate_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        error_x=dict(
            type='data',
            array=LifeTables['Temp_Err'],
            visible=True,
            color='purple',
            thickness=1,
            width=3
            ),
        marker=dict(
            color='purple',
            size=7
            ),
    )
    
    data = [trace_points]
    
    # Ask which functions to add within the plot
    
    print('\n Do you want to add the Logan rate function? y/n \n')
    loris = input()
    
    print('\n Do you want to add the Sharpe and De Michele rate function? y/n \n')
    sdmris = input()
    
    print('\n Do you want to add the Briere rate function? y/n \n')
    briris = input()
    
    print('\n Do you want to add the Linear rate function? y/n \n')
    linris = input()
    
    # Definition of the range for the plots
    T = np.linspace(0, 41, 100)
    
    # Statements to add or not functions to the multiplot
    
    if loris == 'y':
    
        # Import the Logan best fit parameters and errors calculated by 'fittasso'
        Log_BestFitPar = pd.read_csv("../input/.RatePar-simulator/logratepar.txt", sep="\t", header=None)
        Log_BestFitPar.columns = ["Par", "Par_Err"]
        
        # Array with the best fit parameters and their error
        Log_FuncPar = Log_BestFitPar['Par']
        
        # Definition of the Logan function
        LogFunc = Log_FuncPar[0] * (np.exp(Log_FuncPar[1] * T) - np.exp((Log_FuncPar[1] * Log_FuncPar[2]) - ((Log_FuncPar[2] - T)/Log_FuncPar[3])))
    
        # Second plot: add the best fit function
        trace_LogFunc = go.Scatter(
            x=T,
            y=LogFunc,
            name='Logan function'
        )
        
        # Append the plot
        data.append(trace_LogFunc)
    
    
    if sdmris == 'y':
    
        # Import the Sharpe and De Michele best fit parameters and errors calculated by 'fittasso'
        SDM_BestFitPar = pd.read_csv("../input/.RatePar-simulator/SDMratepar.txt", sep="\t", header=None)
        SDM_BestFitPar.columns = ["Par", "Par_Err"]
        
        # Array with the best fit parameters and their error
        SDM_FuncPar = SDM_BestFitPar['Par']
        
        # Definition of the Sharpe and De Michele function
        SDMFunc = (T * np.exp(SDM_FuncPar[0] - (SDM_FuncPar[1] / T))) / (1 + np.exp(SDM_FuncPar[2] - (SDM_FuncPar[3] / T)) + np.exp(SDM_FuncPar[4] - (SDM_FuncPar[5] / T)))
    
        # Second plot: add the best fit function
        trace_SDMFunc = go.Scatter(
            x=T,
            y=SDMFunc,
            name='Sharpe and De Michele function'
        )
        
        # Append the plot
        data.append(trace_SDMFunc)
    
    
    if briris == 'y':
    
        # Import the Briere best fit parameters and errors calculated by 'fittasso'
        Bri_BestFitPar = pd.read_csv("../input/.RatePar-simulator/briratepar.txt", sep="\t", header=None)
        Bri_BestFitPar.columns = ["Par", "Par_Err"]
        
        # Array with the best fit parameters and their error
        Bri_FuncPar = Bri_BestFitPar['Par']
        
        # Definition of the Briere function
        BriFunc = Bri_FuncPar[0] * T * (T - Bri_FuncPar[1]) * pow((Bri_FuncPar[2] - T), (1 / Bri_FuncPar[3]))
    
        # Second plot: add the best fit function
        trace_BriFunc = go.Scatter(
            x=T,
            y=BriFunc,
            name='Briere function'
        )
        
        # Append the plot
        data.append(trace_BriFunc)
    
    
    if linris == 'y':
    
        # Import the Linear best fit parameters and errors calculated by 'fittasso'
        Lin_BestFitPar = pd.read_csv("../input/.RatePar-simulator/linratepar.txt", sep="\t", header=None)
        Lin_BestFitPar.columns = ["Par", "Par_Err"]
        
        # Array with the best fit parameters and their error
        Lin_FuncPar = Lin_BestFitPar['Par']
        
        # Definition of the Linear function
        LinFunc = Lin_FuncPar[0] * T + Lin_FuncPar[1]
    
        # Second plot: add the best fit function
        trace_LinFunc = go.Scatter(
            x=T,
            y=LinFunc,
            name='Linear function'
        )
        
        # Append the plot
        data.append(trace_LinFunc)
    

    # Add all the plots
    fig = go.Figure(data=data)
    
    # Set plot title and layout
    fig.update_layout(
        title='Development rate functions',
        yaxis_title='Development rate (1/d)',
        xaxis_title='Temperature (C)',
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    # Plotting..!
    app.layout = html.Div([
        dcc.Graph(figure=fig)
    ])

    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return

def TreDsurf():

    os.system('echo "TreDsurf() -python- function started " >> ../logfile.log')

    # Read the simulated data
    SimSurf = pd.read_csv("../output/simresults/simulation3D.txt", sep="\t", header=None)

    # Set the header of the experimental life tables
    SimSurf.columns = ["Stage", "Time", "PopDens"]
    
    trace_3Dsurf = go.Scatter3d(
        name='Population density over time',
        x=SimSurf['Stage'],
        y=SimSurf['Time'],
        z=SimSurf['PopDens'],
        mode='lines',
        line=dict(
            color=SimSurf['PopDens'],
            colorscale='plasma',
            colorbar=dict(
                title='Population density'
            )
        )
    )
    
    fig=go.Figure(data=[trace_3Dsurf])
    
    # Set plot title and layout
    fig.update_layout(
        title='Simulated population density',
        scene = {
            'camera_eye': {"x": -0.1, "y": -1, "z": 0.5},
            "aspectratio": {"x": 0.7, "y": 0.7, "z": 0.3},
        },
        font=dict(
            size=11
        ),
        plot_bgcolor='rgba(0,0,0,0)',
        showlegend=True,
        autosize=True,
        height=575,
        legend=dict(
            orientation="h",
            yanchor="bottom",
            y=1.02,
            xanchor="right",
            x=1
        )
    )
    
    return fig

# Plot of the population density of each stage in one single plot (overlapped curves)

def stageresume():
    
    os.system('echo "stageresume() -python- function started " >> ../logfile.log')

    # Read the number of stages simulated (col_max in C code)
    StageCount = pd.read_csv("../input/.SimStorage/SimulatedStages.txt", sep="\t", header=0)
    
    # Undestrand which model is!
    Model = StageCount['Model']
    
    if Model[0] == 1:
        ModelName = ('Manetsch Distributed Delay Model with R(t)')
        
    if Model[0] == 2:
        ModelName = ('Manetsch Distributed Delay Model with Q(t)')

    if Model[0] == 3:
        ModelName = ('Generalized Von Foerster Equation')

    if Model[0] == 4:
        ModelName = ('Integro-diff Von Foerster Equation')
        
    # Take in input the number of simulated stages
    Stages = StageCount['SimStages']
    
    # Cycle to plot the simulated stages
    
    for stage in range(1,Stages[0]+1):
        datafile = ('../output/simresults/h=%d.txt' % stage)
        plotname = ('Stage %d' %stage)
    
        # Import the simulation results
        Simulation = pd.read_csv(datafile, sep="\t", header=None)
        Simulation.columns = ["Time", "PopDens", "Time_err", "PopDens_err"]
    
        # Plot
        
        trace_simul = go.Scatter(
            x=Simulation['Time'],
            y=Simulation['PopDens'],
            mode='lines',
            line={"shape": 'spline'},
            name=plotname,
            showlegend=True,
            error_y=dict(
                type='data',
                array=Simulation['PopDens_err'],
                visible=True,
                thickness=1,
                width=3
                ),
        )
        
        if stage == 1:
            Total_Trace = [trace_simul]
            
        else:
            
            # Append the plot
            Total_Trace.append(trace_simul)
    
    
    # Addition of the traces
    fig = go.Figure(data=Total_Trace)
    
    # Set plot title and layout
    fig.update_layout(
        title='Simulated life stages - '+ModelName,
        yaxis_title='Population density',
        xaxis_title='Time',
        autosize=True,
        height=575,
        font=dict(
            size=15
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    # Set x-axis options
    fig.update_xaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    # Set y-axis options
    fig.update_yaxes(
        showline=True,
        linewidth=2,
        linecolor='black',
        showgrid=True,
        gridwidth=1,
        gridcolor='LightBlue'
    )
    
    return fig

# Plot the population density of each stage (multiple subplots)

def stagedrawer():
    
    os.system('echo "stageresume() -python- function started " >> ../logfile.log')

    # Read the number of stages simulated (col_max in C code)
    StageCount = pd.read_csv("../input/.SimStorage/SimulatedStages.txt", sep="\t", header=0)
    
    # Undestrand which model is!
    Model = StageCount['Model']
    
    if Model[0] == 1:
        ModelName = ('Manetsch Distributed Delay Model with R(t)')
        
    if Model[0] == 2:
        ModelName = ('Manetsch Distributed Delay Model with Q(t)')

    if Model[0] == 3:
        ModelName = ('Generalized Von Foerster Equation')

    if Model[0] == 4:
        ModelName = ('Integro-diff Von Foerster Equation')
        
    # Take in input the number of simulated stages
    Stages = StageCount['SimStages']
    
    # Assignes the number of columns for the graphs
    ColGraph = int((Stages + 1)/2)

    # Crete the plot title
    for stage in range(1, Stages[0] + 1):
        plotname = ('Stage %d' %stage)
        
        if stage == 1:
            SubPlotTitle = ['Stage 1']
        else:
            # Append the plot name
            SubPlotTitle.append(plotname)
    
    # Make subplots
    fig = make_subplots(
            rows = 2,
            cols=ColGraph,
            subplot_titles=(SubPlotTitle)
            )
    
    # Cycle to plot the simulated stages
    
    for stage in range(1,Stages[0]+1):
        datafile = ('../output/simresults/h=%d.txt' % stage)
    
        # Import the simulation results
        Simulation = pd.read_csv(datafile, sep="\t", header=None)
        Simulation.columns = ["Time", "PopDens", "Time_err", "PopDens_err"]
    
        # Definition of the rows and columns
        if stage <= ColGraph:
            Row = 1
            Col = stage
        else:
            Row = 2
            Col = stage - ColGraph
        
        # Plot trace
        
        FigTrace = go.Scatter(
            x=Simulation['Time'],
            y=Simulation['PopDens'],
            mode='lines',
            line={"shape": 'spline'},
            error_y=dict(
                type='data',
                array=Simulation['PopDens_err'],
                visible=True,
                thickness=0.5,
                width=3
                ),
        )
        
        # Addition of the trace
        fig.add_trace(FigTrace, row=Row, col=Col)
        
        # Set x-axis options
        fig.update_xaxes(
            showline=True,
            linewidth=2,
            linecolor='black',
            row=Row,
            col=Col,
            title_text='Time'
        )
        
        if stage == 1 or stage == ColGraph + 1:
        
            # Set y-axis options
            fig.update_yaxes(
                showline=True,
                linewidth=2,
                linecolor='black',
                row=Row,
                col=Col,
                title_text='Population density'
            )
        
        else:
            # Set y-axis options
            fig.update_yaxes(
                showline=True,
                linewidth=2,
                linecolor='black',
                row=Row,
                col=Col,
            )
        
    
    # Set plot title and layout
    fig.update_layout(
        title='Simulated life stages - ' + ModelName,
        showlegend=False,
        autosize=True,
        height=700,
        font=dict(
            size=11
        ),
        plot_bgcolor='rgba(0,0,0,0)',
    )
    
    return fig


# This function plots TreDsurf(), stageresume() and stagedrawer() when called by simulatore (any of the models)

def SimPlotter():
    
    app = dash.Dash(external_stylesheets=[dbc.themes.CYBORG])

    # Import the plots from the specific functions
    TreDplot = TreDsurf()
    OverPlots = stageresume()
    SinglePlots = stagedrawer()
    
    # Create the web page with the tabs
    app.layout = html.Div([
        dcc.Tabs([
            dcc.Tab(label='3D Plot', children=[
                dcc.Graph(
                    figure = TreDplot
                )
            ]),
            dcc.Tab(label='Overlapped stages plot', children=[
                dcc.Graph(
                    figure = OverPlots,
                )
            ]),
            dcc.Tab(label='Single stages plot', children=[
                dcc.Graph(
                    figure = SinglePlots
                )
            ]),
        ])
    ])
    
    # Instructions for the users
    os.system('cat ../input/.Graphics/DashInstructions.txt')
    
    app.run_server(port=port, host=host, debug=True, use_reloader=False)
    
    return
