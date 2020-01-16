type route =
  | Register
  | GamePlay
  | NotFound;

type player = {
  name: string,
  email: string,
};

type state = {
  route,
  player: option(player),
};

type action =
  | RegisterPlayer(player)
  | ChangeRoute(route);

let component = ReasonReact.reducerComponent("App");

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | []
  | ["game"] => GamePlay
  | ["register"] => Register
  | _ => NotFound
  };

let make = _children => {
  ...component,
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },

  initialState: () => {
    route: mapUrlToRoute(ReasonReactRouter.dangerouslyGetInitialUrl()),
    player: None,
  },

  reducer: (action, state) =>
    switch (action) {
    | RegisterPlayer(player) =>
      ReasonReact.Update({...state, player: Some(player)})
    | ChangeRoute(route) => ReasonReact.Update({...state, route})
    },

  render: ({state: {route}}) =>
    <div>
      {switch (route) {
       | Register => <Register />
       | GamePlay => <Game />
       | NotFound => <PageNotFound />
       }}
    </div>,
};