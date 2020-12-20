param ([string]$app, [switch] $kill);


 class App {
    [string] $name
    [string] $location
    [string] $args

    App([string] $n, [string] $l){
        $this.name = $n
        $this.location = $l
        $this.args = $null
    }
    App([string] $n, [string] $l, [string] $a){
        $this.name = $n
        $this.location = $l
        $this.args = $a
    }
 }

function Handle-Application([App] $application) {
    if($kill){
         Stop-Process -Name $application.name -ErrorAction SilentlyContinue
    }
    else {
        if($application.args -eq "") 
            {Start-Process $application.location} 
            else 
            { Start-Process $application.location -ArgumentList $application.args}
        
    }
}

function Run (){
    [App] $spotify = [App]::new("Spotify","%USERPROFILE%\AppData\Local\Microsoft\WindowsApps\Spotify.exe")
    [App] $discord = [App]::new("Discord","%USERPROFILE%\AppData\Local\Discord\Update.exe", "--processStart Discord.exe") 

    switch($app) {
        "DISCORD" {
            Handle-Application $discord
            break
        }
        "SPOTIFY" {
            Handle-Application $spotify
            break
        }
    }

}


Run
